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

    /* gestion plusieurs trucs d un coup
	export
		idem
		export seul afficher env export (a creer avec declare -x(copie de env )) 
		utiliser join OU direct dans printf si export est seul
		export a > rajouter dans env de export mais pas dans env 
		actualisation de la variable si re export 
		tri dans l'ordre ascii
		cas dérreur si exportr =sdfsdfsdf (voir bash)
		bon format a=b

	EXIT %255 ou 256
	exit sans rien ou nb = exit
	exit + plsrs arguments si 1 er = str > "numeric argument"et exit 
	si plsrs arg et 1er int : "too many arguments " et ne pas exit 
	int global 
	*/

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
	int		e;
	char	**cm_sp;

//	f = 0;
//	if (k == 0)
//		f = 1;
	if (full_cmd[1] == NULL)
		display_export();
	while (full_cmd[k])
	{
		if (!check_char_err(full_cmd[k]))
		{
			e = check_eq(full_cmd[k]);
			if (e)
			{
				cm_sp = ft_split(full_cmd[k], '=');
				ft_unset_one(cm_sp[0]);
				ft_unset_one_xp(cm_sp[0]);
				add_env(full_cmd[k]);
				add_env_exp(full_cmd[k]);
				if (cm_sp[0] != NULL)
					free_tab(cm_sp);
			}
			if (!e && !check_db_xp(full_cmd[k]))
				change_xp_env(full_cmd[k]);
		}
		k++;
	}
//	if(f)
//		free_tab(full_cmd);
	return (0);
}
