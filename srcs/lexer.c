/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:01:58 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/09 18:42:59 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*init_token(t_data *data, t_token *token, int type, char *value)
{
	int i;

	i = 0;
	token->value = ft_strdup(value);
	token->e_type = type;
	data->token_tab[i] = token;
	i++;
	printf("%d   %s\n", token->e_type, token->value);
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
	while (lexer->c != '\0' && lexer->index <= ft_strlen(lexer->content))
	{
		if (lexer->c == ' ')
			lexer_advance(lexer);
		else if (lexer->c == '<')
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
			init_token(data, token, CMD, ft_collect_cmd(lexer));
		lexer_advance(lexer);
	}
	return (token);
}

char	*ft_collect_flous(t_lexer *lexer)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	start = lexer->index;
	while ((lexer->c != ' ' || lexer->c != '$') && lexer->c != '\0')
		lexer_advance(lexer);
	end = lexer->index;
	//====================================================
	str = ft_calloc((end - start), sizeof(char));
	//====================================================
	i = 0;
	while (start <= end)
		str[i++] = lexer->content[start++];
	return (str);
}

char	*ft_collect_cmd(t_lexer *lexer)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	start = lexer->index;
	while (lexer->c != '<' && lexer->c != '$' && lexer->c != '>' && lexer->c != '"' && lexer->c != '\'' && lexer->c != ' ' && lexer->c != '\0')
		lexer_advance(lexer);
	end = lexer->index;
	//====================================================
	str = ft_calloc((end - start), sizeof(char));
	//====================================================
	i = 0;
	while (start < end)
		str[i++] = lexer->content[start++];
	return (str);
}

char	*ft_collect_file_name(t_lexer *lexer)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	lexer_advance(lexer);
	start = lexer->index;
	while (lexer->c != ' ' && lexer->c != '\0')
		lexer_advance(lexer);
	end = lexer->index;
	//====================================================
	str = ft_calloc((end - start), sizeof(char));
	//====================================================
	i = 0;
	while (start <= end)
		str[i++] = lexer->content[start++];
	return (str);
}