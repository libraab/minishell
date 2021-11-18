/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:39:02 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/18 12:14:48 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_collect_flous(t_lexer *lexer)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = lexer->index;
	while ((lexer->c != ' ' || lexer->c != '$') && lexer->c != '\0')
		lexer_advance(lexer);
	end = lexer->index;
	str = ft_calloc((end - start) + 1, sizeof(char));
	while (start <= end)
		str[i++] = lexer->content[start++];
	str[i] = 0;
	return (str);
}

char	*ft_collect_cmd(t_lexer *lexer)
{
	char	*cmd;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = lexer->index;
	while (!ft_strchr(OP, lexer->c) && lexer->c != '\0'
		&& lexer->c != '"' && lexer->c != '\'')
		lexer_advance(lexer);
	end = lexer->index;
	cmd = ft_calloc((end - start) + 1, sizeof(char));
	while (start < end)
		cmd[i++] = lexer->content[start++];
	cmd[i] = 0;
	return (cmd);
}

char	*ft_collect_arg(t_lexer *lexer)
{
	char	*arg;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = lexer->index;
	while (!ft_strchr(OP, lexer->c) && lexer->c != '\0')
		lexer_advance(lexer);
	end = lexer->index;
	arg = ft_calloc((end - start) + 1, sizeof(char));
	while (start < end)
		arg[i++] = lexer->content[start++];
	arg[i]= 0;
	return (arg);
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
	while (lexer->c == ' ')
		lexer_advance(lexer);
	while (!ft_strchr(OP, lexer->c) && lexer->c != '\0')
		lexer_advance(lexer);
	end = lexer->index;
	str = ft_calloc(sizeof(char), end - start + 1);
	while (start < end)
		str[i++] = lexer->content[start++];
	str[i]= 0;
	return (str);
}
