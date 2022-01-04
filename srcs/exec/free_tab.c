/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboukhor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:58:55 by hboukhor          #+#    #+#             */
/*   Updated: 2021/11/24 14:58:57 by hboukhor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i])
	{
		free(tabl[i]);
		tabl[i] = NULL;
		i++;
	}
	free(tabl);
	tabl = NULL;
}

void	free_tab_lite(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i])
	{
		free(tabl[i]);
		tabl[i] = NULL;
		i++;
	}
//	free(tabl);
	tabl = NULL;
}
