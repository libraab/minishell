/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:01:58 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/04 16:35:36 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token* init_token(int type, char* value)
{
    t_token *token;

    //=====================================
    token = ft_calloc(1, sizeof(t_token));
    //=====================================

    token->e_type = type;
    token->value = value;
    return (token);
}

t_lexer* init_lexer(char* content)
{
    t_lexer *lexer;
    
    //=====================================
    lexer = ft_calloc(1, sizeof(t_lexer));
    //=====================================

    lexer->content = content;
    lexer->index = 0;
    lexer->c = content[lexer->index];
    return (lexer);
}



void lexer_skip_whitespace(t_lexer* lexer)
{
    while (lexer->c == ' ' || lexer->c == 10)
        lexer_advance(lexer);
}

t_token* lexer_get_next_token(t_lexer* lexer, t_token *token)
{
    while (lexer->c != '\0' && lexer->index< strlen(lexer->content))
    {
        if (lexer->c == ' ' || lexer->c == 10)
            lexer_skip_whitespace(lexer);
        else if (lexer->c == '"')
            init_token(DOUBLE_COT, ft_collect_double_cot(lexer));
        else if (lexer->c == '\'')
            init_token(SIMPLE_COT, ft_collect_simple_cot(lexer));
        else if (lexer->c == '<')
        {
            lexer_advance(lexer);
            if (lexer->c == '<')
                init_token(DL_REDIR, "<<");
            else
                init_token(L_REDIR, "< ");
        }
        else if (lexer->c == '>')
        {
            lexer_advance(lexer);
            if (lexer->c == '>')
                init_token(DR_REDIR, ">>");
            else
                init_token(R_REDIR, "> ");
        }
        else if (lexer->c == '$')
        {
            lexer_advance(lexer);
            if (lexer->c == '$' || lexer->c == ' ')
                init_token(CMD, ft_collect_cmd(lexer));
            else
                init_token(DOLLAR, ft_collect_flous(lexer));
        }
        else
            init_token(CMD, ft_collect_cmd(lexer));
        lexer_advance(lexer);
    }
    return (token);
}

void lexer_advance(t_lexer* lexer)
{
    if (lexer->c != '\0' && lexer->index< ft_strlen(lexer->content))
    {
        lexer->index+= 1;
        lexer->c = lexer->content[lexer->index];
    }
}

char* ft_collect_double_cot(t_lexer* lexer)
{
    char *str;
    int start;
    int end;
    int i;

    lexer_advance(lexer);
    start = lexer->index;
    while (lexer->c != '"') // add the case of inhibited double cot (=if another double cot is inside the double cot)
        lexer_advance(lexer);
    end = lexer->index;

    //====================================================
    str = ft_calloc((end - start), sizeof(char));
    //====================================================

    str[0] = '\0';
    i = 0;
    while (start <= end )
        str[i++] = lexer->content[start++];
    return (str);
}

char* ft_collect_simple_cot(t_lexer* lexer)
{
    char *str;
    int start;
    int end;
    int i;

    lexer_advance(lexer);
    start = lexer->index;
    while (lexer->c != '\'') // add the case of inhibited simple cot (=if another simple cot is inside the simple cot)
        lexer_advance(lexer);
    end = lexer->index;

    //====================================================
    str = ft_calloc((end - start), sizeof(char));
    //====================================================

    str[0] = '\0';
    i = 0;
    while (start <= end )
        str[i++] = lexer->content[start++];
    return (str);
}

char* ft_collect_flous(t_lexer* lexer)
{
    char *str;
    int start;
    int end;
    int i;

    lexer_advance(lexer);
    start = lexer->index;
    while (lexer->c != ' ' || lexer->c != '$')
        lexer_advance(lexer);
    end = lexer->index;

    //====================================================
    str = ft_calloc((end - start), sizeof(char));
    //====================================================

    str[0] = '\0';
    i = 0;
    while (start <= end )
        str[i++] = lexer->content[start++];
    return (str);
}

char* ft_collect_cmd(t_lexer* lexer)
{
    char *str;
    int start;
    int end;
    int i;

    lexer_advance(lexer);
    start = lexer->index;
    while (lexer->c != '<' && lexer->c != '$' && lexer->c != '>' && lexer->c != '"' && lexer->c != '\'')
        lexer_advance(lexer);
    end = lexer->index;

    //====================================================
    str = ft_calloc((end - start), sizeof(char));
    //====================================================

    str[0] = '\0';
    i = 0;
    while (start <= end )
        str[i++] = lexer->content[start++];
    return (str);
}
