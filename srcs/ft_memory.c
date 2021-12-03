/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:35:43 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/03 18:23:50 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_free_token_tab(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb)
	{
		if (data->t_tab[i].value != NULL)
			free (data->t_tab[i].value);
		i++;
	}
	if (data->t_tab != NULL)
		free (data->t_tab);
}

void ft_free_content(t_data *data, char **content)
{
	int		i;

	i = 0;
	while (i < data->tot)
	{
		if (content[i] != NULL)
			free (content[i]);
		i++;
	}
	free(content);
}

void ft_free_cmd_struct(t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
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
		//free (&data->cmd[i]);
		i++;
	}
}
