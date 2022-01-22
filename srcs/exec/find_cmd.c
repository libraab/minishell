/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:05:15 by hboukhor          #+#    #+#             */
/*   Updated: 2022/01/22 11:39:56 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_slash_cmd(char *agmt)
{
	if (access(agmt, F_OK) == 0)
		return (agmt);
	no_infile(agmt);
	return (0);
}

char	*find_cmd(char *agmt, char **env_exec)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env_exec[i])
	{
		// if (agmt[0] == '/')
		// {
		// 	if (access(agmt, F_OK) == 0)
		// 		return (agmt);
		// 	i++;
		// }
		// else
		{
			tmp = ft_strjoin(env_exec[i], agmt);
			if (access(tmp, F_OK) == 0)
				return (tmp);
			free(tmp);
			i++;
		}
	}
	puterr(agmt);
	return (0);
}
