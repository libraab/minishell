/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:01:58 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/08 19:20:25 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_token(t_data *data, int type, char *value)
{
	t_token	*tmp;
	int		j;

	j = 0;
	tmp = ft_calloc(sizeof(t_token), (data->nb + 1));
	while (j < data->nb)
	{
		tmp[j].e_type = data->t_tab[j].e_type;
		tmp[j].value = ft_strdup(data->t_tab[j].value);
		j++;
	}
	tmp[j].e_type = type;
	tmp[j].value = ft_strdup(value);
	if (data->t_tab != NULL)
		ft_free_token_tab(data);
	data->t_tab = tmp;
	data->nb++;
}

int	init_lexer(t_data *data, char *content)
{
	data->lexer.index = 0;
	data->nb = 0;
	data->t_tab = NULL;
	data->lexer.content = ft_change_flous(data, content, 0, 0);
	if (data->lexer.content == NULL)
		return (0);
	data->lexer.c = data->lexer.content[0];
	return (1);
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
	ft_clean_quote(data, 0, 0);
}
