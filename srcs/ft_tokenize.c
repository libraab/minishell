/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:52:01 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/17 09:42:22 by abouhlel         ###   ########.fr       */
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

	tmp = NULL;
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
	if (tmp != NULL)
		free(tmp);
	return (x);
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' && lexer->c != '\0')
		lexer_advance(lexer);
}

void	lexer_get_next_token(t_data *data, t_lexer *lexer)
{
	int	cmd;

	cmd = 0;
	while (lexer->c != '\0' && lexer->index < ft_strlen(lexer->content))
	{
		if (lexer->c == ' ')
			lexer_skip_whitespace(lexer);
		if (lexer->c == '<')
			ft_tokenize_l_redir(data, lexer);
		else if (lexer->c == '>')
			ft_tokenize_r_redir(data, lexer);
		else
			cmd = ft_tokenise_ca(data, lexer, cmd);
	}
	ft_clean_quote(data, 0, 0);
}
