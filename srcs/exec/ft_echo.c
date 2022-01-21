/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:18:54 by hboukhor          #+#    #+#             */
/*   Updated: 2022/01/17 13:48:19 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_opt(char **the_cmd)
{
	int	i;
	int	j;

	if (ft_strncmp(the_cmd[1], "-n", 2) != 0)
		return (1);
	i = 1;
	j = 2;
	while (the_cmd[i])
	{
		if (the_cmd[i][0] == '-' && the_cmd[i][1] == 'n')
		{
			j = 2;
			while (the_cmd[i][j])
			{
				if (the_cmd[i][j] == 'n')
					j++;
				else
					return (i);
			}
			i++;
		}
		else
			return (i);
	}
	return (i);
}

void	echo_no_opt(char **the_cmd)
{
	int	i;

	i = 1;
	while (the_cmd[i])
	{
		printf("%s ", the_cmd[i]);
		i++;
	}
	printf("\n");
}

int	ft_echo(char **the_cmd)
{
	int	i;

	if (the_cmd[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	i = check_opt(the_cmd);
	if (the_cmd[1][0] == '-' && the_cmd[1][1] == 'n' && i > 1)
	{
		while (the_cmd[i])
		{
			ft_putstr(the_cmd[i]);
			i++;
			if (the_cmd[i])
				ft_putstr(" ");
		}
	}
	else
		echo_no_opt(the_cmd);
	ft_change_exit_status(0);
	return (0);
}
