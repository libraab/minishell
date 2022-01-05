/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:05:35 by hboukhor          #+#    #+#             */
/*   Updated: 2021/12/25 15:07:16 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_midcm(t_cmd cm, int fd, int *pp1, char *cmd)
{
	int		inf;
	int		outf;
	int		is_built;

	is_built = check_built(cm.cmd);
	outf = 1;
	if (cm.redir != NULL)
		take_redir(cm.redir, &inf, &outf);
	dup2(fd, STDIN_FILENO);
	close(fd);
	close(pp1[0]);
	if (outf == 1)
	{
		dup2(pp1[1], STDOUT_FILENO);
		close(pp1[1]);
	}
	else
	{
		dup2(outf, STDOUT_FILENO);
		close(outf);
	}
	if (!is_built)
		execve(cmd, cm.full_cmd, exe.env);
	else
		exec_built(cm);
	exit (1);
}

int	middle_cmds(t_cmd cm, int fd)
{
	int		pp1[2];
	int		fid1;
	char	*cmd;
	char	**env_exec;

	int inf;
	int outf = 1;

	int save1;
	int save2;

	cmd = NULL;
	pipe(pp1);
	fid1 = 1;
	if (cm.cmd != NULL)
	{
		env_exec = take_env(cm.cmd);
		cmd = find_cmd(cm.cmd, env_exec);
		free_tab(env_exec);
	}
	// if (cm.cmd == NULL && cm.redir[0] != NULL)
	// {
		save1 = dup(STDIN_FILENO);
		save2 = dup(STDOUT_FILENO);
	// 	dup2(fd, STDIN_FILENO);
	// 	close(fd);
		take_redir(cm.redir, &inf, &outf);
		dup2(save1, STDOUT_FILENO);
		dup2(save2, STDIN_FILENO);
	// 	dup2(pp1[1], STDOUT_FILENO);
	// 	close(pp1[1]);
	// 	return(pp1[0]);
	// }
	if (cmd)
		fid1 = fork();
	if (fid1 == 0)
	{
		if (!check_built(cm.cmd))
		{
			env_exec = take_env(cm.full_cmd[0]);
			cmd = find_cmd(cm.cmd, env_exec);
			free_tab(env_exec);
		}
		do_midcm(cm, fd, pp1, cmd);
	}
	else
	{
		close(fd);
		close(pp1[1]);
		return (pp1[0]);
	}
	return (1);
}
