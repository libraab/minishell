/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:27:38 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/25 15:06:29 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_env_var(t_data *data, char *str, int start, int end)
{
	char	*dol_value;
	char	*newstr;
	int		i;

	i = 0;
	newstr = NULL;
	dol_value = ft_calloc(sizeof(char *), end - start + 1);
	while (i < (end - start))
	{
		dol_value[i] = str[start + i];
		i++;
	}
	dol_value = ft_strcat(dol_value, "=");
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], dol_value, ft_strlen(dol_value)) == 0)
			newstr = data->env[i];
		i++;
	}
	if (newstr == NULL)
	{
		newstr = ft_calloc(sizeof(char), 2);
		newstr = " ";
		return (newstr);
	}
	return (&newstr[ft_strlen(dol_value)]);
}

char	*ft_replace(t_data *data, char *str, int start, int end)
{
	char	*newstr;
	char	*newstr2;
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	(void) data;
	newstr = ft_calloc(sizeof(char *), start);
	newstr2 = ft_calloc(sizeof(char *), ft_strlen(str) - end + 1);
	while (i < start)
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = 0;
	while (str[end + j])
	{
		newstr2[j] = str[end + j];
		j++;
	}
	newstr2[j] = 0;
	s = ft_strdup(newstr);
	newstr = ft_strjoin(newstr, ft_get_env_var(data, str, start + 1, end));
	if (newstr == NULL && newstr2 != NULL)
		newstr = ft_strjoin(s, newstr2);
	else if (newstr == NULL && newstr2 == NULL)
		newstr = s;
	else
		newstr = ft_strjoin(newstr, newstr2);
	return (newstr);
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

char	*ft_change_flous(t_data *data, char *str)
{
	int		i;
	char	c;
	int		dq;
	int		sq;

	i = 0;
	dq = 0;
	sq = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !dq)
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (str[i + 1] && str[i] == c)
				i++;
		}
		if (str[i] == '\'')
			sq = !sq;
		if (str[i] == '"')
			dq = !dq;
		if (str[i] == '$' && str[i + 1] == '?')
			i++;
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] && !dq)
			str = (ft_replace(data, str, i, ft_find_end(str, i + 1, 0)));
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] && dq && !sq)
			str = (ft_replace(data, str, i, ft_find_end(str, i + 1, 1)));
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] && dq && sq)
			str = (ft_replace(data, str, i, ft_find_end(str, i + 1, 2)));
		i++;
	}
	return (str);
}
