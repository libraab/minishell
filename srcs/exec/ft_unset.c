/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:18:54 by hboukhor          #+#    #+#             */
/*   Updated: 2021/12/25 15:11:28 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	uns_one_xpeq(char *var)
{
	int		i;
	int		j;
	char	*cm;

	i = 0;
	j = -1;
	cm = ft_strjoin(var, "=");
	while (exe.expenv[i])
	{
		if (ft_strncmp(exe.expenv[i], cm, (ft_strlen(var) + 1)) == 0)
		{
			j = i;
			break ;
		}
		i++;
	}
	if (j != -1)
		rm_env_xp(j);
	free(cm);
}

int	ft_unset_one_xp(char *var)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (exe.expenv[i])
	{
		if (ft_strncmp(exe.expenv[i], var, (ft_strlen(var) + 1)) == 0)
		{
			j = i;
			break ;
		}
		i++;
	}
	if (j != -1)
		rm_env_xp(j);
	uns_one_xpeq(var);
	return (0);
}

void	unset_xpeq(char **f_cmd)
{
	int		k;
	int		i;
	int		j;
	char	*cm;

	k = 1;
	while (f_cmd[k])
	{
		i = 0;
		j = -1;
		cm = ft_strjoin(f_cmd[k], "=");
		while (exe.expenv[i])
		{
			if (ft_strncmp(exe.expenv[i], cm, (ft_strlen(f_cmd[k]) + 1)) == 0)
			{
				j = i;
				break ;
			}
			i++;
		}
		ft_free(cm);
		if (j != -1)
			rm_env_xp(j);
		k++;
	}
}

int	ft_unset_xp(char **full_cmd)
{
	int		i;
	int		k;

	k = 1;
	while (full_cmd[k])
	{
		i = 0;
		while (exe.expenv[i])
		{
			if (ft_strncmp(exe.expenv[i], full_cmd[k],
					(ft_strlen(full_cmd[k]) + 1)) == 0)
			{
				rm_env_xp(i);
				break ;
			}
			i++;
		}
		k++;
	}
	unset_xpeq(full_cmd);
	return (0);
}

int	ft_unset(char **full_cmd)
{
	int		i;
	int		k;
	char	*cm;

	k = 1;
	check_uns_err(full_cmd);
	while (full_cmd[k])
	{
		i = 0;
		cm = ft_strjoin(full_cmd[k], "=");
		while (exe.env[i])
		{
			if (ft_strncmp(exe.env[i], cm, (ft_strlen(full_cmd[k]) + 1)) == 0)
			{
				rm_env(i);
				break ;
			}
			i++;
		}
		ft_free(cm);
		k++;
	}
	ft_unset_xp(full_cmd);
	return (0);
}
