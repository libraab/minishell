/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:01:58 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/25 17:05:47 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_token(t_data *data, int type, char *value)
{
	t_token	*tmp;
	int		j;

	j = 0;
	tmp = malloc(sizeof(t_token) * (data->nb + 1));
	while (j < data->nb)
	{
		tmp[j].e_type = data->token_tab[j].e_type;
		tmp[j].value = data->token_tab[j].value;
		j++;
	}
	tmp[j].e_type = type;
	tmp[j].value = ft_strdup(value);
	free (data->token_tab);
	data->token_tab = tmp;
	data->nb++;
}

void	init_lexer(t_data *data, char *content)
{
	data->lexer->content = ft_change_flous(data, content);
	data->lexer->index = 0;
	data->lexer->c = data->lexer->content[0];
	data->nb = 0;
	data->token_tab = ft_calloc (sizeof(t_token), 1);
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
	ft_clean_quote(data);
}
