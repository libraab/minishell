/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:18:54 by hboukhor          #+#    #+#             */
/*   Updated: 2021/12/25 12:53:07 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char **full_cmd)
{
	if (full_cmd[1] == NULL || (ft_str_isdigit(full_cmd[1]) && !full_cmd[2]))
	{
		ft_putstr("exit\n");
		exit(0);
	}
	else if (!ft_str_isdigit(full_cmd[1]))
	{
		ft_putstr("exit\n");
		ft_putstr("exit: ");
		ft_putstr(full_cmd[1]);
		ft_putstr(": numeric argument required\n");
		exit(0);
	}
	else if (ft_str_isdigit(full_cmd[1]) && full_cmd[2])
	{
		ft_putstr("exit\n");
		ft_putstr("exit: too many arguments\n");
		ft_change_exit_status(0);
	}
}
