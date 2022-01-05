/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:18:54 by hboukhor          #+#    #+#             */
/*   Updated: 2021/12/25 12:36:19 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_db_xp(char *var)
{
	int		i;
	int		j;
	char	*cm;

	i = 0;
	j = 0;
	cm = ft_strjoin(var, "=");
	while (exe.expenv[i])
	{
		if (ft_strncmp(exe.expenv[i], cm, (ft_strlen(cm))) == 0)
		{
			j = 1;
			break ;
		}
		i++;
	}
	free (cm);
	return (j);
}

void	check_uns_err(char **full_cmd)
{
	int	k;
	int	i;

	k = 1;
	while (full_cmd[k])
	{
		if (ft_isdigit(full_cmd[k][0]))
		{
			printf("unset: '%s': not a valid identifier\n", full_cmd[k]);
			ft_change_exit_status(1);
			return ;
		}
		i = 0;
		while (full_cmd[k][i])
		{
			if (!ft_isalnum(full_cmd[k][i]))
			{
				printf("unset: '%s': not a valid identifier\n", full_cmd[k]);
				ft_change_exit_status(1);
				return ;
			}
			i++;
		}
		k++;
	}
}

void	rm_env(int d)
{
	int		i;
	int		j;
	int		k;
	char	**env_tmp;

	i = 0;
	k = 0;
	j = tab_len(exe.env) - 1;
	env_tmp = ft_calloc(sizeof(char *), j + 1);
	while (exe.env[i])
	{
		if (i != d)
		{
			env_tmp[k] = ft_strdup(exe.env[i]);
			k++;
		}
		i++;
	}
	free_tab(exe.env);
	exe.env = env_tmp;
}

void	rm_env_xp(int d)
{
	int		i;
	int		j;
	int		k;
	char	**env_tmp;

	i = 0;
	k = 0;
	j = tab_len(exe.expenv) - 1;
	env_tmp = ft_calloc(sizeof(char *), j + 1);
	while (exe.expenv[i])
	{
		if (i != d)
		{
			env_tmp[k] = ft_strdup(exe.expenv[i]);
			k++;
		}
		i++;
	}
	free_tab(exe.expenv);
	exe.expenv = env_tmp;
}

int	ft_unset_one(char *var)
{
	int		i;
	int		j;
	char	*cm;

	i = 0;
	j = -1;
	cm = ft_strjoin(var, "=");
	while (exe.env[i])
	{
		if (ft_strncmp(exe.env[i], cm, (ft_strlen(var) + 1)) == 0)
		{
			j = i;
			break ;
		}
		i++;
	}
	if (j != -1)
		rm_env(j);
	free(cm);
	return (0);
}
