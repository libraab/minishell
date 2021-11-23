/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:01:58 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/23 16:10:20 by abouhlel         ###   ########.fr       */
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
	data->lexer->content = ft_change_flous(content);
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
	while (lexer->c == ' ' || lexer->c == '\0')
		lexer_advance(lexer);
}

char	*ft_remove_quote(char *str, int x, int y)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	newstr = ft_calloc(sizeof(char *), ft_strlen(str) - 2);
	while (str[i])
	{
		if (i != x && i != y)
		{
			newstr[j] = str[i];
			j++;
		}
		i++;
	}
	newstr[j] = '\0';
	return (newstr);
}

void	ft_clean_quote(t_data *data)
{
	int		i;
	int		j;
	char	c;
	int		start;
	int		end;

	i = 0;
	while (i < data->nb)
	{
		j = 0;
		if (data->token_tab[i].e_type == 7)
		{
			while (data->token_tab[i].value[j])
			{
				if (data->token_tab[i].value[j] == '\'' || data->token_tab[i].value[j] == '"')
				{
					c = data->token_tab[i].value[j];
					start = j;
					j++;
					while (data->token_tab[i].value[j] && data->token_tab[i].value[j] != c)
						j++;
					end = j;
					data->token_tab[i].value = ft_remove_quote(data->token_tab[i].value, start, end);
				}
				j++;
			}
		}
		i++;
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
		else
			cmd = ft_tokenise_ca(data, lexer, cmd);
	}
	ft_clean_quote(data);
}
