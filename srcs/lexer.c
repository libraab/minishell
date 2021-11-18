/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:01:58 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/18 16:24:18 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_set(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;	
	}
	return (0);
}

#include <stdbool.h>
#include <ctype.h>

int	ft_count_tkn_nbr(char *str)
{
	int		tkn = 1;
	bool	copain1 = false;
	bool	copain2 = false;
	
	for (int i = 0; str[i]; i++)
	{
		if (ft_is_set(str[i], "'\""))
		{
			if (str[i] == '\'')
				copain1 = !copain1;
			else
				copain2 = !copain2;
		}
		if (str[i] && str[i] == ' ' && (copain1 || copain2))
			i++;
		if (str[i] && str[i] == ' ' && str[i + 1] != ' ' && isprint(str[i])
		&& !copain1 && !copain2)
			tkn++;
	}
	return (tkn);
}

// int	ft_count_tkn_nbr(char *str)
// {
// 	int		bool_s = 0;
// 	int		bool_d = 0;
// 	int		i;
// 	int		count;

// 	i = 0;
// 	count = 0;
// 	while (str[i])
// 	{
// 		if (ft_is_set(str[i], "'\""))
// 		{
// 			if (str[i] == '\'')
// 				bool_s = !bool_s;
// 			if (str[i] == '"')
// 				bool_d = !bool_d;
// 		}
// 		else if (str[i] != ' ' && (str[i + 1] == ' ' || !str[i + 1]) && !bool_s && !bool_d)
// 			count++;
// 		else if (ft_is_set(str[i], "<>") && str[i + 1] != str[i])
// 			count++;
// 		i++;
// 	}
// 	count++;
// 	return (count);
// }

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
	printf("token nbr is --> %d\n", ft_count_tkn_nbr(content));
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
    while (lexer->c == ' ' || lexer->c == '\0')
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
		else if (lexer->c == '$')
			ft_tokenize_dollar(data, lexer);
		else
			cmd = ft_tokenise_ca(data, lexer, cmd);
		lexer_advance(lexer);
	}
}
