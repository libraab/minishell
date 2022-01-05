/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:18:54 by hboukhor          #+#    #+#             */
/*   Updated: 2021/12/25 15:11:51 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strchr_plus(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i + 1]);
		i++;
	}
	if (s[i] == (char )c)
		return ((char *) s + (i + 1));
	return (NULL);
}

int	check_eq(char *cm)
{
	int	i;

	i = 0;
	while (cm[i])
	{
		if (cm[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	display_export(void)
{
	int		i;
	char	**exp_disp;

	i = 0;
	while (exe.expenv[i])
	{
		exp_disp = ft_split(exe.expenv[i], '=');
		if (exp_disp[1] == NULL)
			printf("declare -x %s=\"\"\n", exp_disp[0]);
		else
			printf("declare -x %s=\"%s\"\n", exp_disp[0], exp_disp[1]);
		free_tab(exp_disp);
		i++;
	}
	return (0);
}

void	change_xp_env(char *cm)
{
	ft_unset_one_xp(cm);
	add_env_exp(cm);
}

int	ft_export(char **full_cmd, int k)
{
	char	**cm_sp;

	if (full_cmd[1] == NULL)
		display_export();
	while (full_cmd[k])
	{
		if (!check_char_err(full_cmd[k]))
		{
			if (check_eq(full_cmd[k]))
			{
				cm_sp = ft_split(full_cmd[k], '=');
				ft_unset_one(cm_sp[0]);
				ft_unset_one_xp(cm_sp[0]);
				add_env(full_cmd[k]);
				add_env_exp(full_cmd[k]);
				if (cm_sp[0] != NULL)
					free_tab(cm_sp);
			}
			if (!check_eq(full_cmd[k]) && !check_db_xp(full_cmd[k]))
				change_xp_env(full_cmd[k]);
		}
		k++;
	}
	return (0);
}
