/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:53:14 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/14 17:38:32 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		find_qs(const char c, int *q, int *sq)
{
	if (c == 34)
		*q += 1;
	if (c == 39)
		*sq += 1;
}

int		skip_qs(const char *s, int i, int *q, int *sq)
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
	return (i);
}

static int	count_words(char const *s, char c)
{
	int		i;
	int		words;
	int		q;
	int		sq;

	sq = 0;
	q = 0;
	words = 0;
	i = 0;
	while (s[i])
	{
		find_qs(s[i], &q, &sq);
		if (q == 1)
		{
			i = skip_qs(s, i, &q, &sq);
			q = 0;
			sq = 0;
		}
		else if (sq == 1)
		{
			i = skip_qs(s, i, &q, &sq);
			q = 0;
			sq = 0;
		}
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static int	words_len(char const *s, char c)
{
	int		i;
	int		len;
	int		q;
	int		sq;

//"hdhdh | jsjsj 'jksfdsfsdsd | jkjks' | aaa | 'sef | s | ds' "
	
	i = 0;
	len = 0;
	sq = 0;
	q = 0;
	if (s[i] == ' ')
	{
		while (s[i] == ' ')
			i++;
	}
	while ((s[i] != c && s[i] != '\0') || (q == 1 || sq == 1))
	{
		find_qs(s[i], &q, &sq);
		/*if (q == 1)
		{
			i += (skip_qs(s, i, &q, &sq) - i);
			len += i;
		}
		else if (sq == 1)
		{
			i += (skip_qs(s, i, &q, &sq) - i);
			len += i;
		}*/
		if (q == 1)
		{
			while (q != 2)
			{
				i++;
				len++;
				find_qs(s[i], &q, &sq);
			}
			//i--;
			//len--;
			q = 0;
			sq = 0;
		}
		else if(sq == 1)
		{
			while (sq != 2)
			{
				i++;
				len++;
				find_qs(s[i], &q, &sq);
			}
			//i--;
			//len--;
			q = 0;
			sq = 0;
		}
		//else 
		//{
		i++;
		len++;
		//}
	}
	return (len);
}

static void	*freememory(char **tableau, int words)
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

static char	**creat_new_tab(char const *s, int words, char c, char **newtab)
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
		newtab[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!newtab[i])
			return (freememory(newtab, i));
		j = 0;
		if (*s == ' ')
		{
			while (*s == ' ')
				s++;
		}
		while (j < len)
		{
			newtab[i][j++] = *(s++);
		}
		newtab[i][j] = '\0';
	}
	newtab[i] = NULL;
	return (newtab);
}

char	**ft_split_pipe(char	const *s, char c)
{
	char	**newtab;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	newtab = (char **)malloc(sizeof(char *) * (words + 1));
	if (!newtab)
		return (NULL);
	newtab = creat_new_tab(s, words, c, newtab);
	//int i = 0;
	// while(newtab[i])
	// {
	// 	printf("TABSSSS ======  %s\n", newtab[i]);
	// 	i++;
	// }
	return (newtab);
}
