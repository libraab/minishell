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

t_token* init_token(t_token *token, int type, char* value)
{
    token->value = ft_strdup(value);
    token->e_type = type;
    return (token);
}

t_lexer* init_lexer(t_lexer *lexer, char* content)
{
    lexer->content = content;
    lexer->index = 0;
    lexer->c = content[lexer->index];
    return (lexer);
}

int lexer_advance(t_lexer* lexer)
{
    if (lexer->c != '\0' && lexer->index < ft_strlen(lexer->content))
    {
        lexer->index++;
        lexer->c = lexer->content[lexer->index];
        return (1);
    }
    return (0);
}

void lexer_skip_whitespace(t_lexer* lexer)
{
    while (lexer->c == ' ' || lexer->c == 10)
        lexer_advance(lexer);
}

bool    ft_char_is_inhibited(t_lexer *lexer, int i)
{
    if (lexer->content[i - 1] == '\\') 
        return (TRUE);
    return (FALSE);
}

t_token* lexer_get_next_token(t_lexer* lexer, t_token *token)
{
    while (lexer->c != '\0' && lexer->index <= ft_strlen(lexer->content) && ft_char_is_inhibited(lexer, lexer->index) == false)
    {
        if (lexer->c == ' ' || lexer->c == 10)
            lexer_skip_whitespace(lexer);
        else if (lexer->c == '"')
            init_token(token, DOUBLE_COT, ft_collect_double_cot(lexer));
        else if (lexer->c == '\'')
            init_token(token, SIMPLE_COT, ft_collect_simple_cot(lexer));
        else if (lexer->c == '<')
        {
            lexer_advance(lexer);
            if (lexer->c == '<')
                init_token(token, DL_REDIR, "<<");
            else
                init_token(token, L_REDIR, "< ");
        }
        else if (lexer->c == '>')
        {
            lexer_advance(lexer);
            if (lexer->c == '>')
                init_token(token, DR_REDIR, ">>");
            else
                init_token(token, R_REDIR, "> ");
        }
        else if (lexer->c == '$' && ft_char_is_inhibited(lexer, lexer->index) == false)
        {
            if (lexer->content[lexer->index + 1] == '$' || lexer->content[lexer->index + 1] == ' ')
                init_token(token, CMD, ft_collect_cmd(lexer));
                // still needs to handle $\$    $ with sp    and $ with sp and blabla
            else
                init_token(token, DOLLAR, ft_collect_flous(lexer));
        }
        else
            init_token(token, CMD, ft_collect_cmd(lexer));
        lexer_advance(lexer);
    }
    return (token);
}

char* ft_collect_double_cot(t_lexer* lexer)
{
    char *str;
    int start;
    int end;
    int i;

    lexer_advance(lexer);
    start = lexer->index;
    while (lexer->c != '"' || (lexer->c == '"' && ft_char_is_inhibited(lexer, lexer->index)))
    {
        end = lexer->index;
        lexer->index++;
        lexer->c = lexer->content[lexer->index];
    }

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
    while (lexer->c != '\'' || (lexer->c == '\'' && ft_char_is_inhibited(lexer, lexer->index)))
    {
        end = lexer->index;
        lexer->index++;
        lexer->c = lexer->content[lexer->index];
    }

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

    start = lexer->index;
    while ((lexer->c != ' ' || lexer->c != '$') && lexer->c != '\0' && lexer->index < ft_strlen(lexer->content))
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
    while (lexer->c != '<' && lexer->c != '$' && lexer->c != '>' && lexer->c != '"' && lexer->c != '\'' && lexer->c != ' ')
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
