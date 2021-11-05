/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:58:24 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/04 16:31:24 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main (void)
{
	char	*entry;
	t_token *token = NULL;
	

	while (1)
	{
		entry = readline("\033[30;47m[minishell] >\033[0m ");
		if (entry)
		{
			lexer_get_next_token(init_lexer(entry), token);
    		printf ("TOKEN(%d, %s)\n", token->e_type, token->value);
			free(entry);
		}
		else
		{
			ft_putendl_fd("Error", 2);
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

