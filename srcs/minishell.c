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

int	main(void)
{
	t_cmd	*cmd;
	t_token *tkn;
	t_lexer *lex;
	char	*entry;
	while (1)
	{
		entry = readline("\033[30;47m[minishell] >\033[0m ");
		if (entry)
		{
			lexer(entry, cmd, tkn, lex);
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
