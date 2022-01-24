/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:06:27 by hboukhor          #+#    #+#             */
/*   Updated: 2022/01/24 15:40:30 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	puterr(char *cmd)
{
	ft_putstr(cmd);
	ft_putstr(": command not found\n");
	ft_change_exit_status(127);
	return ;
}

void	no_infile(char *inf_name)
{
	ft_putstr(inf_name);
	write(1, ": no such file or directory\n", 29);
	ft_change_exit_status(1);
	exit(1);
}
