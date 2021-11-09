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

void	alloc_init(t_data *data)
{
	data->lexer = malloc (sizeof(t_lexer));
	data->token = malloc (sizeof (t_token));
	data->token_tab = malloc (sizeof (t_token));
	data->cmd = NULL;
}

int	main(void)
{
	char	*entry;
	t_data	*data;
	char **content;

	data = malloc(sizeof(t_data));
	alloc_init(data);
	while (1)
	{
		entry = readline("\033[30;47m[minishell] >\033[0m ");
		if (entry)
		{
			add_history(entry);
			content = ft_split(entry, '|');
			data->lexer = init_lexer(data->lexer, content);
			data->token = lexer_get_next_token(data, data->lexer, data->token);
			printf ("TOKEN(%d, %s)\n", data->token->e_type, data->token->value);
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
