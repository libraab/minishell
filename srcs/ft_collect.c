/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:10:14 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/29 14:58:46 by abouhlel         ###   ########.fr       */
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
	while (!ft_char_is_sep(lexer->c) && lexer->content)
		lexer_advance(lexer);
	end = lexer->index;
	cmd = ft_calloc(sizeof(char), end - start + 1);
	while (start < end)
		cmd[i++] = lexer->content[start++];
	cmd[i] = '\0';
	return (cmd);
}

char	*ft_collect_str(t_lexer *lexer)
{
	char	*str;
	char	quote;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = lexer->index;
	while (!ft_char_is_sep(lexer->c) && lexer->content)
	{
		if (lexer->c == '\'' || lexer->c == '"')
		{
			quote = lexer->c;
			lexer_advance(lexer);
			while (lexer->content && lexer->c != quote)
				lexer_advance(lexer);
		}
		lexer_advance(lexer);
	}
	end = lexer->index;
	str = ft_calloc(sizeof(char), end - start + 1);
	while (start < end)
		str[i++] = lexer->content[start++];
	str[i] = '\0';
	return (str);
}

char	*ft_collect_file_name(t_lexer *lexer)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	i = 0;
	lexer_advance(lexer);
	while (lexer->content && lexer->c == ' ')
		lexer_advance(lexer);
	start = lexer->index;
	while (!ft_char_is_sep(lexer->c))
		lexer_advance(lexer);
	end = lexer->index;
	str = ft_calloc(sizeof(char), end - start + 1);
	while (start < end)
		str[i++] = lexer->content[start++];
	str[i] = '\0';
	return (str);
}

char	*ft_delete(char *str, int x, int y)
{
	int		i;
	int		j;
	char	*newstr;

	i = -1;
	j = 0;
	if (!str)
		return (NULL);
	newstr = ft_calloc(sizeof(char *), ft_strlen(str) - 2);
	while (str[++i])
	{
		if (i != x && i != y)
		{
			newstr[j] = str[i];
			j++;
		}
	}
	newstr[j] = '\0';
	if (str)
		free (str);
	return (newstr);
}

void	ft_clean_quote(t_data *d, int i, int j)
{
	int		start;
	int		end;
	char	c;

	while (i < d->nb)
	{
		j = 0;
		while (d->t_tab[i].value[j])
		{
			if (d->t_tab[i].value[j] == '\'' || d->t_tab[i].value[j] == '"')
			{
				c = d->t_tab[i].value[j];
				start = j;
				j++;
				while (d->t_tab[i].value[j] && d->t_tab[i].value[j] != c)
					j++;
				end = j;
				d->t_tab[i].value = ft_delete(d->t_tab[i].value, start, end);
				j -= 2;
			}
			j++;
		}
		i++;
	}	
}
