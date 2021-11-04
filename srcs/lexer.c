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


t_lexer *init_lexer(char *str, t_lexer *lex)
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
        else if (lex->c == '"')
            return lexer_collect_string(lex);
        else if (lex->c = '\'')
            return lexer_advance_with_token(lex, init_token(SIMPLE_COT, lexer_get_current_c_as_str(lex)));
        else if (lex->c = '"')
            return lexer_advance_with_token(lex, init_token(DOUBLE_COT, lexer_get_current_c_as_str(lex)));
        else if (lex->c = '>')
            return lexer_advance_with_token(lex, init_token(R_REDIR, lexer_get_current_c_as_str(lex)));
        else if (lex->c = '<')
            return lexer_advance_with_token(lex, init_token(L_REDIR, lexer_get_current_c_as_str(lex)));
            // case '>>': return lexer_advance_with_token(lex, init_token(DR_REDIR, lexer_get_current_c_as_str(lex)));break;
            // case '<<': return lexer_advance_with_token(lex, init_token(DL_REDIR, lexer_get_current_c_as_str(lex)));break;
        else if (lex->c = '$')
            return lexer_advance_with_token(lex, init_token(DOLLAR, lexer_get_current_c_as_str(lex)));
    }
}
t_token *lexer_collect_string(t_lexer *lex)
{
    
}
char *lexer_get_current_c_as_str(t_lexer *lex);


int lexer(char *str, t_cmd *cmd, t_token *tkn, t_lexer *lex)
{
    tkn = ft_calloc(1, sizeof(t_token));
    cmd = ft_calloc(1, sizeof(t_cmd));
    lex = ft_calloc(1, sizeof(t_lexer));
    init_lexer(str, lex);
    
    
    
}
