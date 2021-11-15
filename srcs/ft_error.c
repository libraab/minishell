/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:09:32 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/15 12:50:11 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(void)
{
	write(2, "ERROR\n", 6);
	exit(EXIT_FAILURE);
}

void	ft_check_invalid_chars(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i++];
			while (str[i] != c)
				i++;
		}
		else if (str[i] == ';' || str[i] == '\\')
			ft_error();
		i++;
	}
}

int	ft_check_cmdless_pipe(char *str)
{
	int	i;
	int	cmd;

	i = 0;
	cmd = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
		{
			if (cmd == 0)
				return (1);
			else
				cmd = 0;
		}
		else if (str[i] != '|' && str[i] != ' ')
		{
			cmd++;
		}
		i++;
	}
	if (cmd == 0)
		return (1);
	return (0);
}
