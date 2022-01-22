/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:18:54 by hboukhor          #+#    #+#             */
/*   Updated: 2022/01/22 11:28:56 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pwd(char **env)
{
	int		i;
	char	*s;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			s = env[i];
		i++;
	}
	return (&s[4]);
}

void	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
		printf("%s\n", get_pwd(g_exe.env));
	else
	{
		printf("%s\n", buf);
		free(buf);
	}
	ft_change_exit_status(0);
}