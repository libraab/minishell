/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:05:35 by hboukhor          #+#    #+#             */
/*   Updated: 2022/01/21 19:31:49 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_cmd(char *cmd)
{
	char	**env_exec;
	char	*cmdf;

	cmdf = NULL;
	env_exec = take_env(cmd);
	if (env_exec)
	{
		cmdf = find_cmd(cmd, env_exec);
		free_tab(env_exec);
	}
	else
		check_built(cmd);
	return (cmdf);
}

void	do_midcm(t_cmd cm, int fd, int *pp1, char *cmd)
{
	cm.is_built2 = check_built(cm.cmd);
	cm.outf2 = 1;
	if (cm.redir != NULL)
		take_redir(cm.redir, &cm.inf2, &cm.outf2);
	dup2(fd, STDIN_FILENO);
	close(fd);
	close(pp1[0]);
	if (cm.outf2 == 1)
	{
		dup2(pp1[1], STDOUT_FILENO);
		close(pp1[1]);
	}
	else
	{
		dup2(cm.outf2, STDOUT_FILENO);
		close(cm.outf2);
	}
	if (!cm.is_built2)
		execve(cmd, cm.full_cmd, g_exe.env);
	else
		exec_built(cm);
	exit (1);
}

void	save_mid_fds(t_cmd cm)
{
	int	save1;
	int	save2;

	cm.outf22 = 1;
	save1 = dup(STDIN_FILENO);
	save2 = dup(STDOUT_FILENO);
	take_redir(cm.redir, &cm.inf22, &cm.outf22);
	dup2(save1, STDOUT_FILENO);
	dup2(save2, STDIN_FILENO);
	close(save1);
	close(save2);
}

void	init_mid_vars(t_cmd *cm)
{
	cm->cmd2 = NULL;
	cm->outf22 = 1;
	cm->fid2 = 1;
}

int	middle_cmds(t_cmd cm, int fd)
{
	int	pp1[2];

	init_mid_vars(&cm);
	pipe(pp1);
	if (cm.cmd != NULL)
		cm.cmd2 = get_cmd(cm.cmd);
	save_mid_fds(cm);
	if (cm.cmd2)
		cm.fid2 = fork();
	if (cm.fid2 == 0)
	{
		if (!check_built(cm.cmd))
			cm.cmd2 = get_cmd(cm.cmd);
		do_midcm(cm, fd, pp1, cm.cmd2);
	}
	else
	{
		close(fd);
		close(pp1[1]);
		return (pp1[0]);
	}
	return (1);
}
