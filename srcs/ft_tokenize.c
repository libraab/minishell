/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:52:01 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/07 20:20:26 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_tokenize_l_redir(t_data *data, t_lexer *lexer)
{
	char	*tmp;

	if (lexer->content[lexer->index + 1] == '<')
	{
		init_token(data, DL_REDIR, "<<");
		lexer_advance(lexer);
	}
	else
		init_token(data, L_REDIR, "<");
	tmp = ft_collect_file_name(lexer);
	init_token(data, FILE_NAME, tmp);
	free(tmp);
}

void	ft_tokenize_r_redir(t_data *data, t_lexer *lexer)
{
	char	*tmp;

	if (lexer->content[lexer->index + 1] == '>')
	{
		init_token(data, DR_REDIR, ">>");
		lexer_advance(lexer);
	}
	else
		init_token(data, R_REDIR, ">");
	tmp = ft_collect_file_name(lexer);
	init_token(data, FILE_NAME, tmp);
	free(tmp);
}

int	ft_tokenise_ca(t_data *data, t_lexer *lexer, int x)
{
	char	*tmp;

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
