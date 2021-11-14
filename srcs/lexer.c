/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:01:58 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/14 17:43:33 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*init_token(t_data *data, t_token *token, int type, char *value)
{
	int	i;

	i = 0;
	token->value = ft_strdup(value);
	token->e_type = type;
	data->token_tab[i] = token;
	i++;
	printf("tkn type is %d && his value is %s\n", data->token->e_type, data->token->value);
	return (token);
}

t_lexer	*init_lexer(t_lexer *lexer, char *content)
{
	lexer->content = content;
	lexer->index = 0;
	lexer->c = content[lexer->index];
	return (lexer);
}

int	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->index < ft_strlen(lexer->content))
	{
		lexer->index++;
		lexer->c = lexer->content[lexer->index];
		return (1);
	}
	return (0);
}

t_token	*lexer_get_next_token(t_data *data, t_lexer *lexer, t_token *token)
{
	int	cmd;

	cmd = 0;
	while (lexer->c != '\0' && lexer->index < ft_strlen(lexer->content))
	{
		if (lexer->c == '<')
		{
			if (lexer->content[lexer->index + 1] == '<')
			{
				init_token(data, token, DL_REDIR, "<<");
				lexer_advance(lexer);
			}
			else
				init_token(data, token, L_REDIR, "<");
			init_token(data, token, FILE_NAME, ft_collect_file_name(lexer));
		}
		else if (lexer->c == '>')
		{
			if (lexer->content[lexer->index + 1] == '>')
			{
				init_token(data, token, DR_REDIR, ">>");
				lexer_advance(lexer);
			}
			else
				init_token(data, token, R_REDIR, ">");
			init_token(data, token, FILE_NAME, ft_collect_file_name(lexer));
		}
		else if (lexer->c == '$')
		{
			if (lexer->content[lexer->index + 1] == '$' || lexer->content[lexer->index + 1] == ' ')
				init_token(data, token, CMD, ft_collect_cmd(lexer));
			else
				init_token(data, token, DOLLAR, ft_collect_flous(lexer));
		}
		else
		{
			if (cmd == 0)
			{
				init_token(data, token, CMD, ft_collect_cmd(lexer));
				cmd = 1;
			}
			else if (lexer->c != '>' && lexer->c != '<' && lexer->c != '$' && lexer->c != '\0' && cmd > 0)
				init_token(data, token, ARG, ft_collect_arg(lexer));
		}
		lexer_advance(lexer);
	}
	return (token);
}
