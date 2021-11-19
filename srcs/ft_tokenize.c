/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:52:01 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/19 15:57:43 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_collect_cmd(t_lexer *lexer)
{
	char	*cmd;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = lexer->index;
	while (!ft_char_is_sep(lexer->c))
		lexer_advance(lexer);
	while (!ft_char_is_sep(lexer->c))
		lexer_advance(lexer); 
	end = lexer->index;
	cmd = ft_calloc((end - start) + 1, sizeof(char));
	while (start < end)
		cmd[i++] = lexer->content[start++];
	cmd[i] = 0;
	return (cmd);
}

char	*ft_collect_file_name(t_lexer *lexer)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	i = 0;
	lexer_advance(lexer);
	start = lexer->index;
	while (!ft_char_is_sep(lexer->c))
		lexer_advance(lexer);
	end = lexer->index;
	str = ft_calloc(sizeof(char), end - start + 1);
	while (start < end)
		str[i++] = lexer->content[start++];
	str[i] = 0;
	return (str);
}

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
	else if (!ft_char_is_sep(lexer->c) && x != 0)
		init_token(data, ARG, ft_collect_cmd(lexer));
	return (x);
}
