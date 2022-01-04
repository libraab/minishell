/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:18:54 by hboukhor          #+#    #+#             */
/*   Updated: 2021/12/30 12:22:58 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	copy_env(char **env)
{
	int		i;
	int		j;

	i = 0;
	j = tab_len(env);
	exe.env = ft_calloc(sizeof(char *), j + 2);
	while (env[i])
	{
		exe.env[i] = ft_strdup(env[i]);
		i++;
	}
	exe.env[i] = ft_strdup("?=0");
}

void	copy_env_two(char **env)
{
	int		i;
	int		j;
	char	**env_tmp;

	i = 0;
	j = tab_len(env);
	env_tmp = ft_calloc(sizeof(char *), j + 1);
	//exe.env = ft_calloc(sizeof(char *), j + 1);
	while (env[i])
	{
	//	if (exe.env[i] != 0)
	//		free(exe.env[i]);
		env_tmp[i] = ft_strdup(env[i]);
		//exe.env[i] = ft_strdup(env[i]);
		i++;
	}
	free_tab(env);
	exe.env = ft_calloc(sizeof(char *), j + 1);
	i = 0;
	while (env_tmp[i])
	{
	//	if (exe.env[i] != 0)
	//		free(exe.env[i]);
		//env_tmp = ft_strdup(env[i]);
		exe.env[i] = ft_strdup(env_tmp[i]);
		i++;
	}
	free_tab(env_tmp);
}

void	ft_change_exit_status(int x)
{
	int	i;

	i = 0;
	while (exe.env[i][0] != '?')
		i++;
	if (ft_strncmp(exe.env[i], "?=", 2) == 0)
	{
		free (exe.env[i]);
		exe.env[i] = ft_strdup(ft_strcat(ft_strdup("?="), ft_itoa(x)));
	}
}
