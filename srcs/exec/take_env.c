/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:06:38 by hboukhor          #+#    #+#             */
/*   Updated: 2022/01/21 18:54:37 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**take_env(char *cm)
{
	char	*tmp;
	char	**path_split;
	int		i;
	int		p;

	p = check_path();
	if (!p && cm[0])
	{
		puterr(cm);
		return (0);
	}
	path_split = ft_split(get_path(g_exe.env), ':');
	i = 0;
	while (path_split[i])
	{
		tmp = ft_strjoin((char *)path_split[i], "/");
		free(path_split[i]);
		path_split[i] = tmp;
		i++;
	}
	return (path_split);
}
