/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:18:54 by hboukhor          #+#    #+#             */
/*   Updated: 2021/12/30 12:17:51 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_env(char *buf, char *buf2)
{
	char	*to_be_exp[3];
// char    *to_be_uns[3];
//  to_be_uns[0] = ft_strdup("PWD=");
// to_be_uns[1] = ft_strdup("OLDPWD=");
//  to_be_uns[2] = 0;
//  ft_unset(to_be_uns);
	to_be_exp[0] = ft_strjoin("OLDPWD=", buf);
	to_be_exp[1] = ft_strjoin("PWD=", buf2);
	to_be_exp[2] = 0;
	free(buf);
	free(buf2);
	ft_export(to_be_exp, 0);
	free(to_be_exp[0]);
	free(to_be_exp[1]);
	//free_tab_lite(to_be_exp);
}

int	ft_cd(char **the_cmd)
{
	char	*buf;
	char	*buf2;

	if (tab_len(the_cmd) > 2)
	{
		printf("cd: too many arguments\n");
		ft_change_exit_status(1);
		return (1);
	}
	buf = getcwd(NULL, 0);
	if (the_cmd[1] == NULL)
	{
		chdir("/Users/abouhlel");
		buf2 = getcwd(NULL, 0);
		change_env(buf, buf2);
		ft_change_exit_status(0);
		return (0);
	}
	if (chdir(the_cmd[1]) != 0)
	{
		printf("cd: %s: no such file or directory\n", the_cmd[1]);
		ft_change_exit_status(1);
		free(buf);
		return (1);
	}
	buf2 = getcwd(NULL, 0);
	change_env(buf, buf2);
	ft_change_exit_status(0);
	return (0);
}
