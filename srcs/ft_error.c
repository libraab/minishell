/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:09:32 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/21 11:54:54 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(int x)
{
	if (x == 0)
		write(2, "Syntax error\n", 13);
	if (x == 1)
		write(2, "ERROR\nInvalid char\n", 19);
	if (x == 2)
		write(2, "ERROR\nUnclosed quote\n", 21);
	if (x == 3)
		write(2, "ERROR\nCommandless pipe\n", 23);
	else
		write(2, "ERROR\n", 6);
	exit(EXIT_FAILURE);
}

void	ft_check_unclosed_quote(char *str)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !dq)
			sq = !sq;
		if (str[i] == '"' && !sq)
			dq = !dq;
		i++;
	}
	if (sq || dq)
		ft_error(2);
}

int	ft_check_cmdless_pipe(char *str, int i, int cmd)
{
	char	c;

	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			cmd = 1;
		}
		else if (str[i] != '|' && str[i] != ' ')
			cmd = 1;
		else if (str[i] == '|')
		{
			if (cmd == 0)
				ft_error(3);
			cmd = 0;
		}
		i++;
	}
	return (cmd);
}

void	ft_check_invalid_chars(char *str)
{
	int		i;
	char	c;

	i = 0;
	ft_check_unclosed_quote(str);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i])
				i++;
		}
		else if (str[i] == ';' || str[i] == '\\')
			ft_error(1);
		i++;
	}
	if (ft_check_cmdless_pipe(str, 0, 0) == 0)
		ft_error(3);
}
