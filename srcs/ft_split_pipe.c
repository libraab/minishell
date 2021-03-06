/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:53:14 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/29 14:51:00 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_words(char const *s, char c)
{
	int		i;
	int		words;
	int		q;
	int		sq;

	init_vars(&i, &words, &q, &sq);
	while (s[i])
	{
		find_qs(s[i], &q, &sq);
		if (q == 1)
			i = skip_qs(s, i, &q, &sq);
		else if (sq == 1)
			i = skip_qs(s, i, &q, &sq);
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

int	words_len(char const *s, char c)
{
	int		i;
	int		len;
	int		q;
	int		sq;

	init_vars(&i, &len, &q, &sq);
	while ((s[i] != c && s[i] != '\0') || (q == 1 || sq == 1))
	{
		find_qs(s[i], &q, &sq);
		if (q == 1)
		{
			find_next_q(s, &i, &len, &q);
			sq = 0;
		}
		else if (sq == 1)
		{
			find_next_sq(s, &i, &len, &sq);
			q = 0;
		}
		i++;
		len++;
	}
	return (len);
}

void	*freememory(char **tableau, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(tableau[i]);
		i++;
	}
	free(tableau);
	return (NULL);
}

char	**creat_new_tab(char const *s, int words, char c, char **newtab)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	while (++i < words)
	{
		while (*s == c)
			s++;
		len = words_len(s, c);
		newtab[i] = ft_calloc(sizeof(char), len + 1);
		if (!newtab[i])
			return (freememory(newtab, i));
		j = 0;
		while (j < len)
		{
			newtab[i][j++] = *(s++);
		}
		newtab[i][j] = '\0';
	}
	newtab[i] = NULL;
	return (newtab);
}

char	**ft_split_pipe(char const *s, char c)
{
	char	**newtab;
	char	**newtab_sp;
	int		words;

	newtab = NULL;
	newtab_sp = NULL;
	if (!s)
		return (NULL);
	words = count_words(s, c);
	newtab = ft_calloc(sizeof(char *), (words + 1));
	if (!newtab)
		return (NULL);
	newtab = creat_new_tab(s, words, c, newtab);
	if (!newtab)
		return (NULL);
	newtab_sp = delet_spaces(newtab);
	return (newtab_sp);
}
