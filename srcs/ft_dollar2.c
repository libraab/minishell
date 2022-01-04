/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:27:38 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/29 15:27:37 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_env_var(char *str, int start, int end)
{
	char	*dol_value;
	char	*env_var;
	int		dol_len;
	char	*env;
	int		i;

	i = 0;
	env_var = NULL;
	env = NULL;
	dol_value = ft_calloc(sizeof(char *), end - start + 1);
	while (i < (end - start))
	{
		dol_value[i] = str[start + i];
		i++;
	}
	dol_value = ft_strcat(dol_value, ft_strdup("="));
	dol_len = ft_strlen(dol_value);
	i = 0;
	while (exe.env[i])
	{
		if (ft_strncmp(exe.env[i], dol_value, dol_len) == 0)
			env_var = ft_strdup(exe.env[i]);
		i++;
	}
	return (ft_free_things(env, env_var, dol_value, dol_len));
}

bool	ft_shall_return(char *str_before, char *replaced, char *str_after)
{
	bool	ret;

	ret = false;
	if (str_before == NULL && replaced == NULL && str_after == NULL)
		ret = true;
	else if (str_before != NULL && replaced == NULL && str_after == NULL)
		ret = true;
	else if (str_before == NULL && replaced != NULL && str_after == NULL)
		ret = true;
	else if (str_before == NULL && replaced == NULL && str_after != NULL)
		ret = true;
	return (ret);
}

char	*get_replace(char *str_before, char *replaced, char *str_after)
{
	if (str_before == NULL && replaced == NULL && str_after == NULL)
		return (NULL);
	if (str_before != NULL && replaced == NULL && str_after == NULL)
		return (str_before);
	if (str_before == NULL && replaced != NULL && str_after == NULL)
		return (replaced);
	if (str_before == NULL && replaced == NULL && str_after != NULL)
		return (str_after);
	return (NULL);
}

char	*get_tmp(char *str_before, char *replaced, char *str_after)
{
	char	*tmp;

	tmp = NULL;
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
	return (tmp);
}

char	*ft_rep(char *str, int start, int end)
{
	char	*str_before;
	char	*str_after;
	char	*replaced;
	char	*tmp;

	tmp = NULL;
	str_after = NULL;
	str_before = NULL;
	str_before = ft_copy_string1(str, start);
	str_after = ft_copy_string2(str, end);
	replaced = ft_get_env_var(str, start + 1, end);
	if (ft_shall_return(str_before, replaced, str_after) == true)
		return (get_replace(str_before, replaced, str_after));
	if (!tmp)
		tmp = get_tmp(str_before, replaced, str_after);
	if (str_before != NULL && replaced != NULL && str_after != NULL)
		return (ft_all(str_before, replaced, str_after, tmp));
	return (tmp);
}
