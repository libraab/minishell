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

/*void    init_token(t_lexer *lex)
{
    lex->content = str;
    lex->index = 0;
    lex->c = str[lex->index];
}

void	lexer_advance(t_lexer *lex)
{
    if (lex->c != '\0' && lex->index < ft_strlen(lex->content))
    {
        lex->index++;
        lex->c = lex->content[lex->index];
    }
}
void	lexer_skip_whitespace(t_lexer *lex)
{
    while (lex->c == 32 || lex->c == '\n')
    {
        lexer_advance(lex);
    }
}
t_token *lexer_get_next_token(t_lexer *lex)
{
    while (lex->c != '\0' && lex->index < ft_strlen(lex->content))
    {
        if(lex->c == 32 || lex->c == '\n')
            lexer_skip_whitespace(lex);
        else if (lex->c = '\'')
            return (lexer_advance_with_token(lex, init_token(SIMPLE_COT, lexer_get_current_c_as_str(lex))));
            //return (lexer_collect_string(lex));
       
        else if (lex->c = '"')
            return lexer_advance_with_token(lex, init_token(DOUBLE_COT, lexer_get_current_c_as_str(lex)));
        else if (lex->c = '>')
            return lexer_advance_with_token(lex, init_token(R_REDIR, lexer_get_current_c_as_str(lex)));
        else if (lex->c = '<')
            return lexer_advance_with_token(lex, init_token(L_REDIR, lexer_get_current_c_as_str(lex)));
        else if (lex->c = '$')
            return lexer_advance_with_token(lex, init_token(DOLLAR, lexer_get_current_c_as_str(lex)));
        // how to do it with the double chevron
    }
}
/*t_token *lexer_collect_string(t_lexer *lex)
{
    char *tkn;
    char *s;

    lexer_advance(lex);
    tkn = ft_calloc(1, sizeof(char));
    tkn[0] = '\0';
    while (lex->c != '"')
    {
        s = lexer_get_current_c_as_str(lex);
        //tkn = free and malloc and add s len
        ft_strcat(tkn, s);
        lexer_advance(lex);
    }
    lexer_advance(lex);
    return (init_token(ALL, tkn));
}*/

/*t_token *lexer_collect_id(t_lexer *lex)
{
    char *tkn;
    char *s;

    lexer_advance(lex);
    tkn = ft_calloc(1, sizeof(char));
    tkn[0] = '\0';
    while (ft_isalnum(lex->c))
    {
        s = lexer_get_current_c_as_str(lex);
        //tkn = free and malloc and add s len
        ft_strcat(tkn, s);
    }
    lexer_advance(lex);
    return (init_token(ALL, tkn));
}

int lexer(char *str, t_token *tkn, t_lexer *lex)
{
    tkn = ft_calloc(1, sizeof(t_token));
    lex = ft_calloc(1, sizeof(t_lexer));
    
    init_token(lex);

    //tkn = (void*)0;
    while ((tkn = lexer_get_next_token(lex)) != (void*)0)
    {
        printf("TOKEN(%d, %s)\n", tkn->e_type, tkn->tkn);
    }
    return (0);
    
}*/


















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
        if (lexer->c == '"')
            init_token(DOUBLE_COT, ft_collect_str(lexer));
        if (lexer->c = '\'')
            init_token(SIMPLE_COT, lexer_get_current_char_as_string(lexer));
        if (lexer->c = '<') 
            return lexer_advance_with_token(lexer, init_token(L_REDIR, lexer_get_current_char_as_string(lexer)));
        if (lexer->c = '>') 
            return lexer_advance_with_token(lexer, init_token(R_REDIR, lexer_get_current_char_as_string(lexer)));
        if (lexer->c = '$')
            return lexer_advance_with_token(lexer, init_token(DOLLAR, lexer_get_current_char_as_string(lexer)));
        /*if (lexer->c = '>>') 
            return lexer_advance_with_token(lexer, init_token(DR_REDIR, lexer_get_current_char_as_string(lexer)));
        if (lexer->c = '<<') 
            return lexer_advance_with_token(lexer, init_token(DL_REDIR, lexer_get_current_char_as_string(lexer)));*/
    }
    return (init_token(TOKEN_EOF, "\0"));
}

void lexer_advance(t_lexer* lexer)
{
    if (lexer->c != '\0' && lexer->index< ft_strlen(lexer->content))
    {
        lexer->index+= 1;
        lexer->c = lexer->content[lexer->index];
    }
}

char* ft_collect_str(t_lexer* lexer)//collect the str of each token (if there is one)
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
    str = ft_calloc(ft_strlen(end - start), sizeof(char));
    //====================================================

    str[0] = '\0';
    i = 0;
    while (start <= end )
        str[i++] = lexer->content[start++];
    //return (init_token(DOUBLE_COT, str));
    return (str);
}

t_token* lexer_collect_id(t_lexer* lexer)
{
    char* value = ft_calloc(1, sizeof(char));
    value[0] = '\0';

    while (isalnum(lexer->c))
    {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }
    return init_token(TOKEN_ID, value);
}

t_token* lexer_advance_with_token(t_lexer* lexer, t_token* token)
{
    lexer_advance(lexer);
    return (token);
}

char* lexer_get_current_char_as_string(t_lexer* lexer)
{
    char* str;
    
    str = ft_calloc(2, sizeof(char));
    str[0] = lexer->c;
    str[1] = '\0';
    return (str);
}
