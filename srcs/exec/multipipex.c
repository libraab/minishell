/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:05:49 by hboukhor          #+#    #+#             */
/*   Updated: 2022/01/21 19:49:29 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void	last_fork(t_data *data, t_cmd cm, int fd)
{
	data->cmd3 = NULL;
	data->inf3 = 0;
	data->fid3 = fork();
	if (data->fid3 == 0)
	{
		if (cm.redir != NULL)
			take_redir(cm.redir, &data->inf3, &data->outf3);
		if (cm.cmd[0] != '/' && g_exe.rs)
			data->cmd3 = get_cmd(cm.cmd);
		else if (cm.cmd[0] == '/' && g_exe.rs)
			data->cmd3 = find_slash_cmd(cm.cmd);
		if (fd != 0)// && cm.redir == NULL)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		//close (fd);
		if (g_exe.rs)
			exit(execve(data->cmd3, cm.full_cmd, g_exe.env));
		//exit(0);
	}
	else
	{
		if (fd != STDIN_FILENO)
			close(fd);
	}
}

void	last_cmd(t_data *data, t_cmd cm, int fd)
{
	int		inf;
	int		outf;
	int		save1;
	int		save2;

	outf = 1;
	// if (get_cmd(cm.cmd) == NULL)
	// {
	// 	printf("%s\n", cm.cmd);
	// 	return ;
	// }
	if (cm.cmd == NULL && cm.redir != NULL)
	{
		save1 = dup(STDIN_FILENO);
		save2 = dup(STDOUT_FILENO);
		take_redir(cm.redir, &inf, &outf);
		dup2(save1, STDOUT_FILENO);
		dup2(save2, STDIN_FILENO);
		close(save1);
		close(save2);
		close(fd);
		return ;
	}
	else if (check_built(cm.cmd))
		exec_last_built(cm, fd);
	else
		last_fork(data, cm, fd);
}

void	do_cm1(t_data *data, int is_built, int *pp0, char *cmd1)
{
	int		inf;
	int		outf;

	outf = 1;
	if (data->cmd[0].redir[0] != NULL)
		take_redir(data->cmd[0].redir, &inf, &outf);
	close(pp0[0]);
	if (outf == 1)
	{
		dup2(pp0[1], STDOUT_FILENO);
		close(pp0[1]);
	}
	close(pp0[1]);
	// if (data->cmd[0].redir[0] != NULL)
	// 	take_redir(data->cmd[0].redir, &inf, &outf);
	if (!is_built && g_exe.rs)
		execve(cmd1, data->cmd[0].full_cmd, g_exe.env);
	else if (is_built && g_exe.rs)
		exec_built(data->cmd[0]);
	exit(0);
}

int	exec_cm1(t_data *data)
{
	init_vars_cm1(data);
	pipe(data->pp0);
	data->cmd1 = check_cmd(data);
	check_red(data->cmd[0].redir);
	if (data->cmd->cmd == NULL && data->cmd[0].redir[0] != NULL)
	{
		no_cmd_redirs(data, data->pp0);
		return (data->pp0[0]);
	}
	if (data->cmd1)
		data->fid = fork();
	if (data->fid == 0)
	{
		if (!check_built(data->cmd->cmd))
			data->cmd1 = get_cmd(data->cmd[0].cmd);
		do_cm1(data, check_built(data->cmd->cmd), data->pp0, data->cmd1);
	}
	else
	{
		//if (data->cmd1)
		//	free(data->cmd1);
		close (data->pp0[1]);
		return (data->pp0[0]);
	}
	return (data->pp0[0]);
}

void	multi_pipex(t_data *data, int fd, int lastcmd)
{
	int		cm_max;
	int		pp0;
	int		the_cm;

	signal(SIGINT, ft_signals_exec);
	signal(SIGQUIT, ft_signals_exec);
	cm_max = data->tot - 1;
	the_cm = cm_max - lastcmd;
	if (lastcmd != 0 && lastcmd == cm_max)
	{
		pp0 = exec_cm1(data);
		multi_pipex(data, pp0, (lastcmd - 1));
	}
	else if (the_cm < cm_max && g_exe.rs)
	{
		pp0 = middle_cmds(data->cmd[the_cm], fd);
		multi_pipex(data, pp0, (lastcmd - 1));
	}
	else if (the_cm == cm_max && g_exe.rs)
		last_cmd(data, data->cmd[cm_max], fd);
}
