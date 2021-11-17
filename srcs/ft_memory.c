/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:35:43 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/17 17:15:10 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_alloc_init(t_data *data)
{
	data->lexer = ft_calloc (sizeof(t_lexer), 1);
	data->token_tab = NULL;
}

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb)
	{
		if (data->token_tab[i].value != NULL)
			free(data->token_tab[i].value);
		i++;
	}
	if (data->token_tab != NULL)
		free (data->token_tab);
	if (data->lexer != NULL)
		free (data->lexer);
	
}
