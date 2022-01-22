/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_exec_built.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:18:54 by hboukhor          #+#    #+#             */
/*   Updated: 2022/01/22 15:06:33 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_built(t_cmd cm)
{
	if (ft_strncmp(cm.cmd, "pwd", 4) == 0)
		ft_pwd();
	if (ft_strncmp(cm.cmd, "cd", 3) == 0)
		ft_cd(cm.full_cmd);
	else if (ft_strncmp(cm.cmd, "echo", 5) == 0)
		ft_echo(cm.full_cmd);
	else if (ft_strncmp(cm.cmd, "env", 4) == 0)
		ft_env();
	else if (ft_strncmp(cm.cmd, "unset", 6) == 0)
		ft_unset(cm.full_cmd);
	else if (ft_strncmp(cm.cmd, "export", 7) == 0)
		ft_export(cm.full_cmd, 1);
	else if (ft_strncmp(cm.cmd, "exit", 5) == 0)
		ft_exit(cm.full_cmd);
}

int	check_built(char *cmd)
{
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (2);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (3);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (4);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (5);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (6);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (7);
	else
		return (0);
}

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
	if (g_exe.rs)
		exec_built(cm);
	dup2(save1, STDOUT_FILENO);
	dup2(save2, STDIN_FILENO);
}
