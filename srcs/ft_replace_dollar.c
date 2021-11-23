/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:27:38 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/23 18:10:21 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_env_var(char **env, char *str)
{
    int     i;
    char    *s;

    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], ft_strcat(str, "="), 5) == 0)
            s = env[i];
        i++;
    }
    return(&s[5]);
}

char    **take_env(char **env)
{
    char    *s;
    char    **path_split;
    int     i;

    s = get_path(env);
    path_split = ft_split(s, ':');
    i = 0;
    while(path_split[i])
    {
        path_split[i] = ft_strjoin((const char *)path_split[i], "/");
        i++;
    }
    return (path_split);
}

char	*ft_get_env_var(char *str, int start, int end)
{
	int		i;
	char 	*var_dst;
	char	*var_src;

	i = 0;
	var_src = ft_calloc(sizeof(char *), end - start + 1);
	while (i < (end - start))
	{
		var_src[i] = str[start + i];
		i++;
	}
	var_dst = getenv(var_src);
	return (str);
}

char	*ft_replace(char *str, int start, int end)
{
	int	i;
	int	j;
	char *newstr;
	char *newstr2;

	i = 0;
	j = 0;
	newstr = ft_calloc(sizeof(char *), start);
	newstr2 = ft_calloc(sizeof(char *), ft_strlen(str) - end + 1);
	while (i < start)
	{
		newstr[i] = str[i];
		i++;
	}
	while (str[end + j])
	{
		newstr2[j] = str[end + j];
		j++;
	}
	newstr = ft_strjoin(newstr, "ABOUHLEL"); //ft_get_env_var(str, start, end));
	newstr = ft_strjoin(newstr, newstr2);
	if (str != NULL)
		free (str);
	str = newstr;
	return (str);
}

int	ft_find_end(char *str, int i, int x)
{
	if (x == 0)
	{
		while (str[i] && str[i] != ' ' && str[i] != '$')
		i++;	
	}
	if (x == 1)
	{
		while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '"')
		i++;	
	}
	if (x == 2)
	{
		while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '\'')
		i++;	
	}
	return (i);
}

char	*ft_change_flous(char *str)
{
	int		i;
	char	c;
	int		dq = 0;
	int		sq = 0;
	
	i = 0;
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
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] && !dq)
			str = (ft_replace(str, i, ft_find_end(str, i + 1, 0)));
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] && dq && !sq)
			str = (ft_replace(str, i, ft_find_end(str, i + 1, 1)));
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] && dq && sq)
			str = (ft_replace(str, i, ft_find_end(str, i + 1, 2)));
		i++;
	}
	return (str);
}
