/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:56:46 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/17 09:58:08 by abouhlel         ###   ########.fr       */
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
# include "../libft/libft.h"

typedef enum e_type
{
	R_REDIR,
	L_REDIR,
	DR_REDIR,
	DL_REDIR,
	FILE_NAME,
	DOLLAR,
	CMD,
	ARG,
}	t_TYPE;
typedef struct s_token
{
	t_TYPE	e_type;	
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
	char	**full_cmd;
	char	**redir;
}			t_cmd;

typedef struct s_data
{
	t_lexer	lexer;
	t_cmd	*cmd;
	t_token	*t_tab;
	int		i;
	int		tot;
	int		nb;
	char	c;
	char	**env;
}			t_data;

//================================================================
//						* R E A D L I N E *						//
//================================================================

char		*readline(const char *prompt);
int			add_history(const char *string_for_history);
int			rl_on_new_line(void);
void		rl_redisplay(void);
void		rl_replace_line(const char *buffer, int something);

//================================================================
//						* L E X E R *							//
//================================================================

void		lexer_get_next_token(t_data *data, t_lexer *lexer);
void		init_token(t_data *data, int type, char *value);
int			init_lexer(t_data *data, char *content);
void		ft_init_data(t_data *data);
int			ft_prompt(char *entry, t_data *data);
char		*ft_collect_file_name(t_lexer *lexer);
void		lexer_skip_whitespace(t_lexer *lexer);
char		*ft_collect_cmd(t_lexer *lexer);
char		*ft_collect_str(t_lexer *lexer);
int			lexer_advance(t_lexer *lexer);
void		ft_error(int x);
int			ft_entry_is_only_sp(char *str);
int			ft_check_cmdless_pipe(char *str, int i, int cmd);
char		**ft_split_pipe(char const *s, char c);
void		ft_alloc_init(t_data *data);
void		ft_check_invalid_chars(char *str);
void		lexer_skip_whitespace(t_lexer *lexer);
void		ft_tokenize_l_redir(t_data *data, t_lexer *lexer);
void		ft_tokenize_r_redir(t_data *data, t_lexer *lexer);
int			ft_tokenise_ca(t_data *data, t_lexer *lexer, int x);
void		ft_stock_cmd(t_data *data, int i, int j, int k);
int			ft_count_arg(t_data *data);
int			ft_count_redir(t_data *data);
int			ft_count_cmd_nbr(char **str);
int			ft_count_tab(char **tableau);
int			ft_char_is_sep(char c);
char		*get_path(char **env);
char		**take_env(char **env);
void		ft_check_unclosed_quote(char *str);
char		*ft_change_flous(t_data *data, char *str, int sq, int dq);
char		*ft_replace(t_data *data, char *str, int start, int end);
int			ft_find_end(char *str, int i, int x);
void		ft_clean_quote(t_data *data, int i, int j);
char		*ft_get_env_var(t_data *data, char *str, int start, int end);
int			ft_skip_quote(char *str, int i, int dq, int sq);
char		*ft_copy_string1(char *str, int start);
char		*ft_copy_string2(char *str, int end);
char		*ft_all(char *str_before, char *replaced, char *str_after, char *tmp);
char		**ft_clone_env(char **env);
int			ft_count_tab(char **tableau);
void		ft_print_cmd_tab(t_data *data, int i, int j, int k);

//=============================================================================
//						* S P L I T *										 //
//=============================================================================

char		**ft_split_pipe(char const *s, char c);
void		find_qs(const char c, int *q, int *sq);
int			skip_qs(const char *s, int i, int *q, int *sq);
void		find_next_q(char const *s, int *i, int *len, int *q);
void		find_next_sq(char const *s, int *i, int *len, int *sq);
char		**delet_spaces(char **newtab);
void		init_vars(int *a, int *b, int *c, int *d);

//=============================================================================
//						* F R E E *											 //
//=============================================================================

void		ft_free_content(char **content);
void		ft_free_token_tab(t_data *data);
void		ft_free_cmd_struct(t_data *data, int i, int j, int k);
void		ft_free_data_env(char **data_env);
char		*ft_free_things(char *env, char *env_var, char *dol_value, int dol_len);

#endif
