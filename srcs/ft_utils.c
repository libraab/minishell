/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:01:35 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/17 08:02:49 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_path(char *cmd)
{
	char *path;
	char *good_path;
	char **tableau;
	int i;
	i = -1;
	path = getenv("PATH");
	tableau = ft_split(path, ':');
	while (tableau[++i])
		tableau[i] = ft_strjoin(tableau[i], "/");
	i = -1;
	while (tableau[++i])
		tableau[i] = ft_strjoin(tableau[i], cmd);
	i = -1;
	while (tableau[++i])
	{
		if (access(tableau[i], F_OK) != -1)
		{
			good_path = tableau[i];
			free_tab(tableau);
			return (good_path);
		}
	}
	return (NULL);
}