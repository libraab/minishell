/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:52:01 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/25 15:11:24 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_tokenize_l_redir(t_data *data, t_lexer *lexer)
{
	if (lexer->content[lexer->index + 1] == '<')
	{
		init_token(data, DL_REDIR, "<<");
		lexer_advance(lexer);
	}
	else
		init_token(data, L_REDIR, "<");
	init_token(data, FILE_NAME, ft_collect_file_name(lexer));
}

void	ft_tokenize_r_redir(t_data *data, t_lexer *lexer)
{
	if (lexer->content[lexer->index + 1] == '>')
	{
		init_token(data, DR_REDIR, ">>");
		lexer_advance(lexer);
	}
	else
		init_token(data, R_REDIR, ">");
	init_token(data, FILE_NAME, ft_collect_file_name(lexer));
}

int	ft_tokenise_ca(t_data *data, t_lexer *lexer, int x)
{
	if (x == 0)
	{
		init_token(data, CMD, ft_collect_cmd(lexer));
		x = 1;
	}
	else if (lexer->c == '$' && x != 0)
		init_token(data, DOLLAR, ft_collect_cmd(lexer));
	else if (!ft_char_is_sep(lexer->c) && x != 0)
		init_token(data, ARG, ft_collect_arg(lexer));
	return (x);
}
