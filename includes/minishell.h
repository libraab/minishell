/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:56:46 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/16 10:31:07 by abouhlel         ###   ########.fr       */
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
	char	*value; ////malloc'd via strdup in lexer.c line 17
	int		nb;
}			t_token;

typedef struct s_lexer
{
	char			c;
	unsigned int	index;
	char			*content; //malloc'd via strdup in lexer.c line 25
}					t_lexer;
typedef struct s_cmd
{
	char	*cmd;
	char	**full_cmd;
	char	**redir;
}			t_cmd;

typedef struct s_data
{
	t_lexer	*lexer; //malloc'd in memory.c line 17
	t_token	*token; //malloc'd in memory.c line 18
	t_cmd	**cmd; //malloc'd in minishell.c line 61
	t_token	**token_tab;
	int		cmd_index;
	int		tot;
}			t_data; // malloc'd in minishell.c line 49

//================================================================
//						* L E X E R *							//
//================================================================

t_token		*lexer_get_next_token(t_data *data, t_lexer *lexer, t_token *token);
void		init_token(t_data *data, int type, char *value);
void		init_lexer(t_data *data, char *content);
char		*ft_collect_file_name(t_lexer *lexer);
void		lexer_skip_whitespace(t_lexer *lexer);
char		*ft_collect_flous(t_lexer *lexer);
char		*ft_collect_cmd(t_lexer *lexer);
char		*ft_collect_arg(t_lexer *lexer);
int			lexer_advance(t_lexer *lexer);
void		ft_free(t_data *data);
void		ft_error(void);
int			ft_check_cmdless_pipe(char *str);
char		**ft_split_pipe(char const *s, char c);
void		ft_alloc_init(t_data *data);
void		ft_check_invalid_chars(char *str);
int			ft_count_tkn_nbr(char *str);
void		ft_tokenize_l_redir(t_data *data, t_lexer *lexer, t_token *token);
void		ft_tokenize_r_redir(t_data *data, t_lexer *lexer, t_token *token);
void		ft_tokenize_dollar(t_data *data, t_lexer *lexer, t_token *token);
int			ft_tokenise_ca(t_data *data, t_lexer *lexer, t_token *token, int x);
void		ft_stock_cmd(t_data *data);
int			ft_count_arg(t_data *data);

//================================================================
//						* S P L I T *							//
//================================================================

char		**ft_split_pipe(char const *s, char c);
void		find_qs(const char c, int *q, int *sq);
int			skip_qs(const char *s, int i, int *q, int *sq);
void		find_next_q(char const *s, int *i, int *len, int *q);
void		find_next_sq(char const *s, int *i, int *len, int *sq);
char		**delet_spaces(char **newtab);
void		init_vars(int *a, int *b, int *c, int *d);

#endif
