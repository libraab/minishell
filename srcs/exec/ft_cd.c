/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:18:54 by hboukhor          #+#    #+#             */
/*   Updated: 2022/01/24 12:47:17 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_env(char *buf, char *buf2)
{
	char	*to_be_exp[3];

	to_be_exp[0] = ft_strjoin("OLDPWD=", buf);
	to_be_exp[1] = ft_strjoin("PWD=", buf2);
	to_be_exp[2] = 0;
	free(buf);
	free(buf2);
	ft_export(to_be_exp, 0);
	free(to_be_exp[0]);
	free(to_be_exp[1]);
}

char	*ft_get_home(char **env)
{
	int		i;
	char	*str;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			str = env[i];
		i++;
	}
	return (&str[5]);
}

int	ft_cd_errors(char **the_cmd, int x, char *buf)
{
	if (x == 0)
		ft_putstr("cd: too many arguments\n");
	if (x == 1)
	{
		ft_putstr("cd: ");
		ft_putstr(the_cmd[1]);
		ft_putstr(": no such file or directory\n");
		free(buf);
	}
	if (x == 2)
	{
		ft_putstr("cd: ");
		ft_putstr(the_cmd[1]);
		ft_putstr(": invalid option\ncd: usage: cd [-L|-P] [dir]\n");
		free(buf);
	}
	ft_change_exit_status(1);
	return (1);
}

int	ft_cd(char **cmd)
{
	char	*buf;
	char	*buf2;

	if (tab_len(cmd) > 2)
		return (ft_cd_errors(cmd, 0, NULL));
	buf = getcwd(NULL, 0);
	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] != '\0')
		return (ft_cd_errors(cmd, 2, buf));
	if (cmd[1] == NULL || !ft_strncmp(cmd[1], "~", 2))
		chdir(ft_get_home(g_exe.env));
	if (cmd[1] && cmd[1][0] == '-')
		chdir(get_oldpwd(g_exe.env));
	if (cmd[1] && cmd[1][0] != '-' && (cmd[1][0] != '~'
		|| (cmd[1][0] == '~' && cmd[1][1] != '\0')) && chdir(cmd[1]) != 0)
		return (ft_cd_errors(cmd, 1, buf));
	buf2 = getcwd(NULL, 0);
	change_env(buf, buf2);
	ft_change_exit_status(0);
	return (0);
}
