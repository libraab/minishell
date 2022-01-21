/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:05:26 by hboukhor          #+#    #+#             */
/*   Updated: 2022/01/17 15:32:43 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_path(void)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (g_exe.env[i])
	{
		if (ft_strncmp(g_exe.env[i], "PATH=", 5) == 0)
		{
			j = 1;
			break ;
		}
		i++;
	}
	if (j == 0)
		return (0);
	return (1);
}

char	*get_path(char **env)
{
	int		i;
	char	*s;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			s = env[i];
		i++;
	}
	return (&s[5]);
}
