/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:05:49 by hboukhor          #+#    #+#             */
/*   Updated: 2021/12/25 15:10:31 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_last_built(t_cmd cm, int fd)
{
	int	inf;
	int	outf;
	int	save1;
	int	save2;

	outf = 1;
	save1 = dup(STDIN_FILENO);
	save2 = dup(STDOUT_FILENO);
	if (cm.redir != NULL)
		take_redir(cm.redir, &inf, &outf);
	if (fd != 0)
		close(fd);
	exec_built(cm);
	dup2(save1, STDOUT_FILENO);
	dup2(save2, STDIN_FILENO);
}

void	last_fork(t_cmd cm, int fd)
{
	int		fid;
	char	*cmd;
	int		inf;
	int		outf;
	char	**env_exec;

	fid = 1;
	env_exec = take_env(cm.cmd);
	if (cm.redir != NULL)
		take_redir(cm.redir, &inf, &outf);
	cmd = find_cmd(cm.cmd, env_exec);
	free_tab(env_exec);
	if (cmd)
		fid = fork();
	if (fid == 0)
	{
		env_exec = take_env(cm.cmd);
		if (cm.redir != NULL)
			take_redir(cm.redir, &inf, &outf);
		cmd = find_cmd(cm.cmd, env_exec);
		if (fd != 0)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		execve(cmd, cm.full_cmd, exe.env);
		exit(1);
	}
	else
	{
		if (fd != STDIN_FILENO)
			close(fd);
	}
}

void	last_cmd(t_cmd cm, int fd)
{
	int		inf;
	int		outf;
	int		is_built;
	int		save1;
	int		save2;

	outf = 1;
	if (cm.cmd == NULL && cm.redir != NULL)
	{
		save1 = dup(STDIN_FILENO);
		save2 = dup(STDOUT_FILENO);
		take_redir(cm.redir, &inf, &outf);
		dup2(save1, STDOUT_FILENO);
		dup2(save2, STDIN_FILENO);
		return ;
	}
	is_built = check_built(cm.cmd);
	if (is_built)
		exec_last_built(cm, fd);
	else
		last_fork(cm, fd);
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
		dup2(pp0[1], STDOUT_FILENO);
	else if (outf != 1)
	{
		dup2(outf, STDOUT_FILENO);
		close(outf);
	}
	close(pp0[1]);
	if (data->cmd[0].redir[0] != NULL)
		take_redir(data->cmd[0].redir, &inf, &outf);
	if (!is_built)
		execve(cmd1, data->cmd[0].full_cmd, exe.env);
	else
		exec_built(data->cmd[0]);
	exit(1);
}

int	exec_cm1(t_data *data)
{
	char	*cmd1;
	int		fid;
	int		pp0[2];
	int		is_built;
	char	**env_exec;

	is_built = 0;
	cmd1 = NULL;
	is_built = check_built(data->cmd->cmd);
	pipe(pp0);
	fid = fork();
	if (fid == 0)
	{
		if (!is_built)
		{
			env_exec = take_env(data->cmd[0].cmd);
			cmd1 = find_cmd(data->cmd[0].cmd, env_exec);
			free_tab(env_exec);
		}
		do_cm1(data, is_built, pp0, cmd1);
	}
	else
	{
		close (pp0[1]);
		return (pp0[0]);
	}
	return (pp0[0]);
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
	else if (the_cm < cm_max)
	{
		pp0 = middle_cmds(data->cmd[the_cm], fd);
		multi_pipex(data, pp0, (lastcmd - 1));
	}
	else if (the_cm == cm_max)
		last_cmd(data->cmd[cm_max], fd);
}
