/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:35:43 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/01 18:48:03 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_alloc_init(t_data *data)
{
	data->lexer = ft_calloc (sizeof(t_lexer), 1);
	data->t_tab = NULL;
}

void	ft_free(t_data *data, int x)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	if (x == 0)
	{
	}
	if (x == 1)
	{
		while (i < data->nb)
		{
			if (data->t_tab[i].value != NULL)
				free (data->t_tab[i].value);
			i++;
		}
		if (data->t_tab != NULL)
			free (data->t_tab);
	}
	if (x == 2)
	{
		while (i < data->tot)
		{
			if (data->cmd[i].cmd != NULL)
				free (data->cmd[i].cmd);
			if (data->cmd[i].full_cmd != NULL)
			{
				j = 0;
				while (data->cmd[i].full_cmd[j])
				{
					free (data->cmd[i].full_cmd[j]);
					j++;
				}			
			}
			free (data->cmd[i].full_cmd);
			if (data->cmd[i].redir != NULL)
			{
				k = 0;
				while (data->cmd[i].redir[k])
				{
					free (data->cmd[i].redir[k]);
					k++;
				}
			}
			free (data->cmd[i].redir);
			i++;
		}
		free (&data->cmd[i]);
	}
}
