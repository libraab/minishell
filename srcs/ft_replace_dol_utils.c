/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_dol_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 12:25:22 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/17 10:47:20 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_skip_quote(char *str, int i, int dq, int sq)
{
	char	c;

	if (str[i] == '\'' && !dq && !sq)
	{
		c = str[i];
		i++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (i);
}

char	*ft_copy_string1(char *str, int start)
{
	char	*newstr;
	int		i;

	i = 0;
	if (start == 0)
		return (NULL);
	newstr = ft_calloc(sizeof(char *), start + 1);
	while (i < start)
	{
		newstr[i] = str[i];
		i++;
	}
	return (newstr);
}

char	*ft_copy_string2(char *str, int end)
{
	char	*newstr;
	int		j;
	int		str_len;

	j = 0;
	str_len = strlen(str);
	if (end == str_len)
		return (NULL);
	newstr = ft_calloc(sizeof(char *), ft_strlen(str) - end + 1);
	while (str[end + j])
	{
		newstr[j] = str[end + j];
		j++;
	}
	return (newstr);
}

char	*ft_all(char *before, char *replaced, char *after, char *tmp)
{
	tmp = ft_strjoin(before, replaced);
	free (before);
	free (replaced);
	replaced = ft_strjoin(tmp, after);
	free (after);
	free (tmp);
	return (replaced);
}

int	ft_find_end(char *str, int i, int x)
{
	if (x == 0)
	{
		while (str[i] && (ft_isalpha(str[i]) || str[i] == '_')
			&& str[i] != ' ' && str[i] != '$')
			i++;
	}
	if (x == 1)
	{
		while (str[i] && (ft_isalpha(str[i]) || str[i] == '_')
			&& str[i] != ' ' && str[i] != '$' && str[i] != '"')
			i++;
	}
	if (x == 2)
	{
		while (str[i] && (ft_isalpha(str[i]) || str[i] == '_')
			&& str[i] != ' ' && str[i] != '$' && str[i] != '\'')
			i++;
	}
	return (i);
}
