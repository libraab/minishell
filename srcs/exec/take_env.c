/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboukhor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:06:38 by hboukhor          #+#    #+#             */
/*   Updated: 2021/11/24 15:06:40 by hboukhor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**take_env(char *cm)
{
	char	*s;
	char	*tmp;
	char	**path_split;
	int		i;
	int		p;

	p = check_path();
	if (!p)
		puterr(cm);
	s = get_path(exe.env);
	path_split = ft_split(s, ':');
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
