/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:01:35 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/19 15:10:25 by abouhlel         ###   ########.fr       */
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
		if (data->token_tab[i].e_type == 7)
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
