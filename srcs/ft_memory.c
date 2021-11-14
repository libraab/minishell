/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:35:43 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/14 17:36:32 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_alloc_init(t_data *data)
{
	data->lexer = malloc (sizeof(t_lexer));
	data->token = malloc (sizeof (t_token));
	data->token_tab = malloc (sizeof (t_token));
	data->cmd = NULL;
}

void	ft_free(t_data *data)
{
	if (data->lexer->content != NULL)
		free (data->lexer->content);
	if (data->token->value != NULL)
		free (data->token->value);
	if (data->lexer != NULL)
		free (data->lexer);
	if (data->token != NULL)
		free (data->token);
}
