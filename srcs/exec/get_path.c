/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:05:26 by hboukhor          #+#    #+#             */
/*   Updated: 2021/12/25 12:33:05 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_path(void)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (exe.env[i])
	{
		if (ft_strncmp(exe.env[i], "PATH=", 5) == 0)
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
