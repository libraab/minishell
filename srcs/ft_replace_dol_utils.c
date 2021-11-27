/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_dol_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 12:25:22 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/27 18:02:57 by abouhlel         ###   ########.fr       */
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
	newstr = ft_calloc(sizeof(char *), start);
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

	j = 0;
	newstr = ft_calloc(sizeof(char *), ft_strlen(str) - end + 1);
	while (str[end + j])
	{
		newstr[j] = str[end + j];
		j++;
	}
	return (newstr);
}

char	*ft_check_null(char *newstr)
{
	if (newstr == NULL)
	{
		newstr = ft_calloc(sizeof(char), 2);
		newstr = " ";
		return (newstr);
	}
	return (0);
}
