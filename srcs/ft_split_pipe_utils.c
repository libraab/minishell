/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:38:09 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/25 18:19:22 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_qs(const char c, int *q, int *sq)
{
	if (c == 34)
		*q += 1;
	if (c == 39)
		*sq += 1;
}

void	init_vars(int *a, int *b, int *c, int *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

int	skip_qs(const char *s, int i, int *q, int *sq)
{
	if (*q == 1)
	{
		while (s[i] && *q != 2)
		{
			i++;
			find_qs(s[i], q, sq);
		}
	}
	else if (*sq == 1)
	{
		while (s[i] && *sq != 2)
		{
			i++;
			find_qs(s[i], q, sq);
		}
	}
	*q = 0;
	*sq = 0;
	return (i);
}

void	find_next_q(char const *s, int *i, int *len, int *q)
{
	int	sq;
	int	j;
	int	l;

	j = *i;
	l = *len;
	sq = 0;
	while (s[j] && *q != 2)
	{
		j++;
		l++;
		find_qs(s[j], q, &sq);
	}
	*i = j;
	*len = l;
	*q = 0;
}

void	find_next_sq(char const *s, int *i, int *len, int *sq)
{
	int	q;
	int	j;
	int	l;

	j = *i;
	l = *len;
	q = 0;
	while (s[j] && *sq != 2)
	{
		j++;
		l++;
		find_qs(s[j], &q, sq);
	}
	*i = j;
	*len = l;
	*sq = 0;
}

char	**delet_spaces(char **newtab)
{
	int	i;

	i = 0;
	while (newtab[i])
	{
		//newtab[i] = ft_strtrim(newtab[i], " ");
		i++;
	}
	return (newtab);
}

void	ft_check_unclosed_quote(char *str)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (str[i++])
	{
		if (str[i] == '\'')
			sq = !sq;
		if (str[i] == '"')
			dq = !dq;
	}
	if (sq || dq)
		ft_error();
}