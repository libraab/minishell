/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:56:46 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/14 17:32:58 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define OP "<>$ "

typedef struct s_token
{
	enum
	{
		R_REDIR,
		L_REDIR,
		DR_REDIR,
		DL_REDIR,
		DOLLAR,
		FILE_NAME,
		CMD,
		ARG,
	} e_type;
	char	*value;
}			t_token;
typedef struct s_lexer
{
	char			c;
	unsigned int	index;
	char			*content;
}					t_lexer;
typedef struct s_cmd
{
	char	*cmd;
	char	*full_cmd;
	char	**redir;
}			t_cmd;

typedef struct s_data
{
	t_lexer	*lexer;
	t_cmd	*cmd;
	t_token	*token;
	t_token	**token_tab;
}			t_data;

t_token		*lexer_get_next_token(t_data *data, t_lexer* lexer, t_token *token);
t_token		*init_token(t_data *data, t_token *token, int type, char* value);
t_lexer		*init_lexer(t_lexer *lexer, char *content);
char		*ft_collect_file_name(t_lexer *lexer);
void		lexer_skip_whitespace(t_lexer* lexer);
char		*ft_collect_flous(t_lexer* lexer);
char		*ft_collect_cmd(t_lexer* lexer);
char		*ft_collect_arg(t_lexer *lexer);
int			lexer_advance(t_lexer* lexer);
void		ft_free(t_data *data);
void		ft_error(void);
int			ft_check_cmdless_pipe(char *str);
char		**ft_split_pipe(char	const *s, char c);
void		ft_alloc_init(t_data *data);

#endif
