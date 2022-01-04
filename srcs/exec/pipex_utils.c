/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboukhor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:06:27 by hboukhor          #+#    #+#             */
/*   Updated: 2021/11/24 15:06:29 by hboukhor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	puterr(char *cmd)
{
	ft_putstr(cmd);
	ft_putstr(": command not found\n");
	ft_change_exit_status(127);
	return ;
	//WEXITSTATUS pour recperer le code DE l exit
}

void	no_infile(char *inf_name)
{
	ft_putstr(inf_name);
	write(1, ": no such file or directory\n", 29);
	ft_change_exit_status(1);
	exit(1);
}
