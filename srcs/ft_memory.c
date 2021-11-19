/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:35:43 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/19 14:58:55 by abouhlel         ###   ########.fr       */
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
	if (data->token_tab != NULL)
		free (data->token_tab);
	if (data->lexer != NULL)
		free (data->lexer);
}
