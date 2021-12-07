/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:27:38 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/07 17:56:41 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_env_var(t_data *data, char *str, int start, int end)
{
	char	*dol_value;
	char	*newstr;
	int		i;
	int		size_dol;

	i = 0;
	newstr = NULL;
	dol_value = ft_calloc(sizeof(char *), end - start + 1);
	while (i < (end - start))
	{
		dol_value[i] = str[start + i];
		i++;
	}
	dol_value = ft_strcat(dol_value, "=");
	size_dol = ft_strlen(dol_value);
	free(dol_value);
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], dol_value, size_dol) == 0)
			newstr = data->env[i];
		i++;
	}
	if (!ft_check_null(newstr))
		return (&newstr[size_dol]);
	return (newstr);
}

char	*ft_replace(t_data *data, char *str, int start, int end)
{
	char	*newstr;
	char	*newstr2;
	char	*s;
	char	*tmp;

	newstr = ft_copy_string1(str, start);
	newstr2 = ft_copy_string2(str, end);
	s = ft_strdup(newstr);
	tmp = ft_strjoin(newstr, ft_get_env_var(data, str, start + 1, end));
	free(newstr);
	newstr = ft_strdup(tmp);
	free(tmp);
	if (newstr == NULL && newstr2 != NULL)
		newstr = ft_strjoin(s, newstr2);
	else if (newstr == NULL && newstr2 == NULL)
		newstr = s;
	else
	{
		tmp = ft_strjoin(newstr, newstr2);
		free(newstr);
		newstr = ft_strdup(tmp);
		free(tmp);
	}
	free(s);
	free(newstr2);
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

char	*ft_change_flous(t_data *data, char *str, int sq, int dq)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = ft_strdup(str);
	while (str[i])
	{
		i = ft_skip_quote(str, i, dq, sq);
		if (str[i] == '\'')
			sq = !sq;
		else if (str[i] == '"')
			dq = !dq;
		else if (str[i] == '$' && (str[i + 1] == '?' || str[i + 1] == '$'))
			i++;
		else if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] && !dq)
		{
			free(newstr);
			newstr = (ft_replace(data, str, i, ft_find_end(str, i + 1, 0)));
			free(str);
			str = ft_strdup(newstr);
		}
		else if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] && dq && !sq)
		{
			free(newstr);
			str = (ft_replace(data, str, i, ft_find_end(str, i + 1, 1)));
			free(str);
			str = ft_strdup(newstr);
		}
		else if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] && dq && sq)
		{
			free(newstr);
			str = (ft_replace(data, str, i, ft_find_end(str, i + 1, 2)));
			free(str);
			str = ft_strdup(newstr);
		}
		i++;
	}
	free(newstr);
	return (str);
}
