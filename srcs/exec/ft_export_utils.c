/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:46:08 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/24 19:58:06 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	crea_envexp(void)
{
	int		i;
	int		j;

	i = 0;
	j = tab_len(g_exe.env);
	g_exe.expenv = ft_calloc(sizeof(char *), j + 1);
	while (g_exe.env[i])
	{
		g_exe.expenv[i] = ft_strdup(g_exe.env[i]);
		i++;
	}
}

void	add_env(char *var)
{
	int		i;
	int		j;
	int		k;
	char	**env_tmp;
	char	**cm_sp;

	i = 0;
	k = 0;
	cm_sp = ft_split(var, '=');
	ft_unset_one(cm_sp[0]);
	free_tab(cm_sp);
	j = tab_len(g_exe.env) + 1;
	env_tmp = ft_calloc(sizeof(char *), j + 1);
	while (g_exe.env[i])
	{
		env_tmp[k] = ft_strdup(g_exe.env[i]);
		i++;
		k++;
	}
	env_tmp[k] = ft_strdup(var);
	free_tab(g_exe.env);
	g_exe.env = env_tmp;
}

void	env_exp(char **env)
{
	int		i;
	int		j;
	char	**tmpexpenv;

	tmpexpenv = g_exe.expenv;
	i = 0;
	j = tab_len(env);
	g_exe.expenv = ft_calloc(sizeof(char *), j + 1);
	while (env[i])
	{
		g_exe.expenv[i] = ft_strdup(env[i]);
		i++;
	}
	free_tab(tmpexpenv);
	free_tab(env);
}

void	add_env_exp(char *var)
{
	int		i;
	int		j;
	char	**env_tmp;

	i = - 1;
	j = tab_len(g_exe.expenv) + 1;
	env_tmp = ft_calloc(sizeof(char *), j + 1);
	while (g_exe.expenv[++i])
	{
		if (ft_strncmp(env_tmp[i - 1], var, 1) < 0)
		{
			env_tmp[i] = ft_strdup(var);
			i++;
		}
		env_tmp[i] = ft_strdup(g_exe.expenv[i]);
	}
	free_tab(g_exe.expenv);
	g_exe.expenv = env_tmp;
}

int	check_char_err(char *the_cm)
{
	if (!ft_isalpha(the_cm[0]))
	{
		printf("export: '%s': not a valid identifier\n", the_cm);
		ft_change_exit_status(1);
		return (1);
	}
	return (0);
}
