/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:01:58 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/15 15:18:00 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_count_tkn_nbr(char *str)
{
	int	i;
	int	x;
	char	c;

	i = 0;
	x = 0;
	while(str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i++];
			while (str[i] != c)
				i++;
			x++;
		}
		else if (str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
			x++;
		else if ((str[i] == '>' || str[i] == '<') && str[i + 1] != str[i])
			x++;
		i++;
	}
	return (x);
}

t_token	*init_token(t_data *data, t_token *token, int type, char *value)
{
	token->value = ft_strdup(value);
	token->e_type = type;
	printf("tkn type is %d && his value is %s\n", data->token->e_type, data->token->value);
	return (token);
}

t_lexer	*init_lexer(t_lexer *lexer, char *content)
{
	lexer->content = ft_strdup(content);
	lexer->index = 0;
	lexer->c = content[lexer->index];
	lexer->tkn_nbr = ft_count_tkn_nbr(content);
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
