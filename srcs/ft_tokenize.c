/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bledda <bledda@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:52:01 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/07 11:39:14 by bledda           ###   ########.fr       */
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
	char *tmp = ft_collect_file_name(lexer);
	init_token(data, FILE_NAME, tmp);
	free(tmp);
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
	char *tmp = ft_collect_file_name(lexer);
	init_token(data, FILE_NAME, tmp);
	free(tmp);
}

int	ft_tokenise_ca(t_data *data, t_lexer *lexer, int x)
{
	char *tmp;
	
	if (x == 0)
	{
		tmp = ft_collect_str(lexer);
		init_token(data, CMD, tmp);
		x = 1;
	}
	else if (lexer->c == '$' && x != 0)
	{
		tmp = ft_collect_cmd(lexer);
		init_token(data, DOLLAR, tmp);
	}
	else if (!ft_char_is_sep(lexer->c) && x != 0)
	{
		tmp = ft_collect_str(lexer);
		init_token(data, ARG, tmp);
	}
	free(tmp);
	return (x);
}
