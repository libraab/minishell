/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:52:01 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/15 20:04:47 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_tokenize_l_redir(t_data *data, t_lexer *lexer, t_token *token)
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

void	ft_tokenize_r_redir(t_data *data, t_lexer *lexer, t_token *token)
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

void	ft_tokenize_dollar(t_data *data, t_lexer *lexer, t_token *token)
{
	if (lexer->content[lexer->index + 1] == '$'
		|| lexer->content[lexer->index + 1] == ' ')
		init_token(data, CMD, ft_collect_cmd(lexer));
	else
		init_token(data, DOLLAR, ft_collect_flous(lexer));
}

int	ft_tokenise_c_a(t_data *data, t_lexer *lexer, t_token *token, int cmd)
{
	if (cmd == 0)
	{
		init_token(data, CMD, ft_collect_cmd(lexer));
		cmd = 1;
	}
	else if (!ft_strchr(OP, lexer->c) && lexer->c != '\0' && cmd > 0)
		init_token(data, ARG, ft_collect_arg(lexer));
	return (cmd);
}
