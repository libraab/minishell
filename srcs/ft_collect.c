/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:39:02 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/14 17:39:59 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	char	*cmd;
	int		start;
	int		end;
	int		i;

	start = lexer->index;
	while (!ft_strchr(OP, lexer->c) && lexer->c != '\0' && lexer->c != '"' && lexer->c != '\'')
		lexer_advance(lexer);
	end = lexer->index;
	//====================================================
	cmd = ft_calloc((end - start), sizeof(char));
	//====================================================
	i = 0;
	while (start < end)
		cmd[i++] = lexer->content[start++];
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
	//===========================================
	arg = ft_calloc((end - start), sizeof(char));
	//===========================================
	while (start < end)
		arg[i++] = lexer->content[start++];
	return (arg);
}

char	*ft_collect_file_name(t_lexer *lexer)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	lexer_advance(lexer);
	start = lexer->index;
	while (lexer->c == ' ')
		lexer_advance(lexer);
	while (!ft_strchr(OP, lexer->c) && lexer->c != '\0')
		lexer_advance(lexer);
	end = lexer->index;
	//============================================
	str = ft_calloc((end - start), sizeof(char));
	//============================================
	i = 0;
	while (start <= end)
		str[i++] = lexer->content[start++];
	return (str);
}
