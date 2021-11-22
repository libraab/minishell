/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:01:35 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/22 19:00:27 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	*get_path(char *cmd)
// {
// 	char	*path;
// 	char	*good_path;
// 	char	**tableau;
// 	int		i;

// 	i = -1;
// 	path = getenv("PATH");
// 	tableau = ft_split(path, ':');
// 	while (tableau[++i])
// 		tableau[i] = ft_strjoin(tableau[i], "/");
// 	i = -1;
// 	while (tableau[++i])
// 		tableau[i] = ft_strjoin(tableau[i], cmd);
// 	i = -1;
// 	while (tableau[++i])
// 	{
// 		if (access(tableau[i], F_OK) != -1)
// 		{
// 			good_path = tableau[i];
// 			free_tab(tableau);
// 			return (good_path);
// 		}
// 	}
// 	return (NULL);
// }

int	ft_char_is_sep(char c)
{
	if (c == ' ' || c == '\0')
		return (1);
	if (c == '>' || c == '<')
		return (1);
	else
		return (0);
}

int	ft_count_cmd_nbr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_count_arg(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < data->nb)
	{
		if (data->token_tab[i].e_type >= 5)
			count++;
		i++;
	}
	return (count);
}

int	ft_count_redir(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < data->nb)
	{
		if (data->token_tab[i].e_type < 6)
			count++;
		i++;
	}
	return (count);
}
//************************************
char	*ft_change_flous(t_data *data)
{
	int		i;
	char	*str;
	
	i = 0;
	if (variable == 0)
		str[0] = 0;
	return (str);
}
//************************************


char *get_path(char **env)
{
    int     i;
    char    *s;

    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
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


char    *find_cmd(char *agmt, char **path_split)
{
    int i;
    char **full_cmd;

    i = 0;
    full_cmd = ft_split(agmt, ' ');;
    while(path_split[i])
    {
        if(access(ft_strjoin(path_split[i], full_cmd[0]), F_OK) == 0)
            return (ft_strjoin(path_split[i], full_cmd[0]));
        i++;
    }
    return(0);
}