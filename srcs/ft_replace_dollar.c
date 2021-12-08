/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:27:38 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/08 17:25:25 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_env_var(t_data *data, char *str, int start, int end)
{
	char	*env_var;
	char	*dol_value;
	int		dol_len;
	int		i;
	char  *env;
	i = 0;
	env_var = NULL;
	dol_value = ft_calloc(sizeof(char *), end - start + 1);
	while (i < (end - start))
	{
		dol_value[i] = str[start + i];
		i++;
	}
	dol_value = ft_strcat(dol_value, "=");
	dol_len = ft_strlen(dol_value);
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], dol_value, dol_len) == 0)
			env_var = ft_strdup(data->env[i]);
		i++;
	}
	free (dol_value);
	if (env_var != NULL)
	{
		env = ft_strdup(env_var + dol_len);
		free(env_var);
	}
	else
		env = NULL;
	return (env);
}

char	*ft_replace(t_data *data, char *str, int start, int end)
{
	char	*str_before;
	char	*str_after;
	char	*replaced;
	char	*tmp;

	str_before = ft_copy_string1(str, start);
	str_after = ft_copy_string2(str, end);
	replaced = ft_get_env_var(data, str, start + 1, end);
	if (str_before == NULL && replaced == NULL && str_after == NULL)
		return (NULL);
	if (str_before != NULL && replaced == NULL && str_after == NULL) 
		return (str_before);
	if (str_before == NULL && replaced != NULL && str_after == NULL)
		return (replaced);
	if (str_before == NULL && replaced == NULL && str_after != NULL)
		return (str_after);
	if (str_before != NULL && replaced != NULL && str_after == NULL)
	{
		tmp = ft_strjoin(str_before, replaced);
		free (str_before);
		free (replaced);
	}
	if (str_before != NULL && replaced == NULL && str_after != NULL) 
	{
		tmp = ft_strjoin(str_before, str_after);
		free (str_before);
		free (str_after);
	}
	if (str_before == NULL && replaced != NULL && str_after != NULL)
	{
		tmp = ft_strjoin(replaced, str_after);
		free (replaced);
		free (str_after);
	}
	if (str_before != NULL && replaced != NULL && str_after != NULL)
	{
		tmp = ft_strjoin(str_before, replaced);
		free (str_before);
		free (replaced);
		replaced = ft_strjoin(tmp, str_after);
		free (str_after);
		free (tmp);
		return (replaced);
	}
	return (tmp);
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
	newstr = NULL;
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
			if (newstr == NULL)
				break;
			free(newstr);
			newstr = NULL;
		}
		else if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] && dq && !sq)
		{
			free(newstr);
			newstr = (ft_replace(data, str, i, ft_find_end(str, i + 1, 1)));
			free(str);
			str = ft_strdup(newstr);
			free(newstr);
			newstr = NULL;
		}
		else if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] && dq && sq)
		{
			free(newstr);
			newstr = (ft_replace(data, str, i, ft_find_end(str, i + 1, 2)));
			free(str);
			str = ft_strdup(newstr);
			free(newstr);
			newstr = NULL;
		}
		i++;
	}
	return (str);
}
