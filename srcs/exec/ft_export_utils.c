/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:46:08 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/25 12:46:00 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	crea_envexp(void)
{
	int		i;
	int		j;

	i = 0;
	j = tab_len(exe.env);
	exe.expenv = ft_calloc(sizeof(char *), j + 1);
	while (exe.env[i])
	{
		exe.expenv[i] = ft_strdup(exe.env[i]);
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
	j = tab_len(exe.env) + 1;
	env_tmp = ft_calloc(sizeof(char *), j + 1);
	while (exe.env[i])
	{
		env_tmp[k] = ft_strdup(exe.env[i]);
		i++;
		k++;
	}
	env_tmp[k] = ft_strdup(var);
	free_tab(exe.env);
	exe.env = env_tmp;
}

void	env_exp(char **env)
{
	int		i;
	int		j;
	char	**tmpexpenv;

	tmpexpenv = exe.expenv;
	i = 0;
	j = tab_len(env);
	exe.expenv = ft_calloc(sizeof(char *), j + 1);
	while (env[i])
	{
		exe.expenv[i] = ft_strdup(env[i]);
		i++;
	}
	free_tab(tmpexpenv);
	free_tab(env);
}

void	add_env_exp(char *var)
{
	int		i;
	int		j;
	int		k;
	char	**env_tmp;

	i = 0;
	k = 0;
	j = tab_len(exe.expenv) + 1;
	env_tmp = ft_calloc(sizeof(char *), j + 1);
	while (exe.expenv[i])
	{
		env_tmp[k] = ft_strdup(exe.expenv[i]);
		i++;
		k++;
	}
	env_tmp[k] = ft_strdup(var);
	free_tab(exe.expenv);
	exe.expenv = env_tmp;
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
