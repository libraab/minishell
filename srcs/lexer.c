/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:01:58 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/17 13:24:44 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_tkn_nbr(char *str)
{
	int		i;
	int		x;
	char	c;

	i = 0;
	x = 0;
	while (str[i])
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

void	init_token(t_data *data, int type, char *value)
{
	static int	i = 0;

	data->token_tab[i].value = ft_strdup(value); 
	data->token_tab[i].e_type = type;
	i++;
	if (i == data->nb)
		i = 0;
}

void	init_lexer(t_data *data, char *content)
{
	data->lexer->content = ft_strdup(content);
	data->lexer->index = 0;
	data->lexer->c = content[0];
	data->nb = ft_count_tkn_nbr(content);
	data->token_tab = ft_calloc (sizeof(t_token), data->nb + 1);
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

void	lexer_skip_whitespace(t_lexer *lexer)
{
    while (lexer->c == 32 || lexer->c == '\n')
    {
        lexer_advance(lexer);
    }
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
		else if (lexer->c == '$')
			ft_tokenize_dollar(data, lexer);
		else
			cmd = ft_tokenise_ca(data, lexer, cmd);
		lexer_advance(lexer);
	}
}
