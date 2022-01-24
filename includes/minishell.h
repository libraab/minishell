/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:56:46 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/24 12:56:13 by abouhlel         ###   ########.fr       */
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
	int		inf2;
	int		outf2;
	int		is_built2;
	int		fid2;
	char	*cmd2;
	int		inf22;
	int		outf22;
}			t_cmd;

typedef struct s_data
{
	t_lexer	lexer;
	t_cmd	*cmd;
	t_token	*t_tab;
	char	**env;
	int		i;
	int		tot;
	int		nb;
	int		tmp;
	char	*newstr;
	int		j;
	char	*cmd1;
	int		fid;
	int		pp0[2];
	int		fid3;
	char	*cmd3;
	int		inf3;
	int		outf3;
}			t_data;

typedef struct s_exe
{
	char	**env;
	char	**expenv;
	int		rs;
	int		inv_cm;
	int		hdc;
	int		forked;
}			t_exe;

t_exe	g_exe;



# define PANIC(x) do{\
	fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, strerror(errno));\
	if (x > 0) exit(x);\
}while(0)

//================================================================
//					* R E A D L I N E *							//
//================================================================

char	*readline(const char *prompt);
int		add_history(const char *string_for_history);
int		rl_on_new_line(void);
void	rl_redisplay(void);
void	rl_forced_update_display(void);
void	rl_clear_message (void);
void    echo_control_seq(int c);
void	rl_replace_line(const char *buffer, int something);

//================================================================
//					* L E X E R _ S R C S *						//
//================================================================

// MINISHELL.c
void	ft_stock_cmd(t_data *d, int i, int j, int k);
int		ft_prompt(char *entry, t_data *data);
void	make_exec(char *entry, t_data *data);
// LEXER.c
void	init_token(t_data *data, int type, char *value);
int		init_lexer(t_data *data, char *content);
int		lexer_advance(t_lexer *lexer);
int		ft_count_tab(char **tableau);
char	**ft_clone_env(char **env);
// FT_UTILS.c
int		ft_char_is_sep(char c);
int		ft_count_cmd_nbr(char **str);
int		ft_count_arg(t_data *data);
int		ft_count_redir(t_data *data);
char	**delet_spaces(char **newtab);
// FT_TOKENIZE.c
void	ft_tokenize_l_redir(t_data *data, t_lexer *lexer);
void	ft_tokenize_r_redir(t_data *data, t_lexer *lexer);
int		ft_tokenise_ca(t_data *data, t_lexer *lexer, int x);
void	lexer_skip_whitespace(t_lexer *lexer);
void	lexer_get_next_token(t_data *data, t_lexer *lexer);
// FT_SPLIT_PIPE.c
int		count_words(char const *s, char c);
int		words_len(char const *s, char c);
void	*freememory(char **tableau, int words);
char	**creat_new_tab(char const *s, int words, char c, char **newtab);
char	**ft_split_pipe(char const *s, char c);
// FT_PLIT_PIPE_UTILS.c
void	find_qs(const char c, int *q, int *sq);
void	init_vars(int *a, int *b, int *c, int *d);
int		skip_qs(const char *s, int i, int *q, int *sq);
void	find_next_q(char const *s, int *i, int *len, int *q);
void	find_next_sq(char const *s, int *i, int *len, int *sq);
// FT_SIGNAL.c
void	ft_sig_hd(int sig);
void	ft_signals(int sig);
int		ft_exit_entry(void);
int		ft_entry_is_only_sp(char *str);
void	ft_init_data(t_data *d);
// FT_PRINT.c
void	ft_print_cmd_tab(t_data *data, int i, int j, int k);
// FT_MEMORY.c
void	ft_free_token_tab(t_data *data);
void	ft_free_double(char **tabl);
void	ft_free(char *ptr);
void	ft_free_cmd_struct(t_data *data, int i, int j, int k);
char	*ft_free_things(char *env, char *env_var, char *dolv, int len);
// FT_ERROR.c
void	ft_error(int x);
void	ft_check_unclosed_quote(char *str);
int		ft_check_cmdless_pipe(char *str, int i, int cmd);
void	ft_check_invalid_chars(char *str);
// FT_DOLLAR1.c
int		ft_val(int val1, int val2);
int		ft_skip_simple_quote(char *str, int i, int sq, int dq);
void	ft_switch(char c, int *sq, int *dq);
int		ft_skip_dollar(char *str, int index);
char	*ft_change_flous(t_data *d, char *s, int sq, int dq);
// FT_DOLLAR2.c
char	*ft_get_env_var(char *str, int start, int end);
bool	ft_shall_return(char *str_before, char *replaced, char *str_after);
char	*get_replace(char *str_before, char *replaced, char *str_after);
char	*get_tmp(char *str_before, char *replaced, char *str_after);
char	*ft_rep(char *str, int start, int end);
// FT_DOLLAR3.c
char	*ft_copy_string1(char *str, int start);
char	*ft_copy_string2(char *str, int end);
char	*ft_all(char *before, char *replaced, char *after, char *tmp);
int		ft_end(char *str, int i, int x);
// FT_COLLECT.c
char	*ft_collect_cmd(t_lexer *lexer);
char	*ft_collect_str(t_lexer *lexer);
char	*ft_collect_file_name(t_lexer *lexer);
char	*ft_delete(char *str, int x, int y);
void	ft_clean_quote(t_data *d, int i, int j);

//*****************************************************************************
//								* E X E C *									 //
//*****************************************************************************

void	free_tab(char **tabl);
void	free_tab_lite(char **tabl);
void	ft_signals(int sig);
void	ft_signals_exec(int sig);

//*****************************************************************************
//								* S R C *									 //
//*****************************************************************************

char	*get_path(char **env);
int		tab_len(char **tabl);
char	**take_env(char *cm);
int		check_path(void);
char	*find_cmd(char *agmt, char **env_exec);

char	*find_slash_cmd(char *agmt);

char	*get_cmd(char *cmd);

//*****************************************************************************
//						* M U L T I P I P E X *								 //
//*****************************************************************************

int		open_inf(char *infile_name, int *inf);
int		open_outf(char *outfil_nam, int *outf);
void	open_outf_db(char *outfil_nam, int *outf);
int		take_redir(char **red, int *inf, int *outf);
int		ft_search_file(char **red, int i);
void	last_cmd(t_data *data, t_cmd cm, int fd);
int		exec_cm1(t_data *data);
void	multi_pipex(t_data *data, int fd, int lastcmd);

//*****************************************************************************
//						* M U L T I P I P E X _ H D*						 //
//*****************************************************************************

void	last_cmd_hd(char *av_last, char **env, char *outfile_name, int fd);
int		exec_cm1_hd(char **av, char **env, char **env_exec);
void	hd(char **red);
int		middle_cmds(t_cmd cm, int fd);

//*****************************************************************************
//						* P I P E X _ U T I LS *							 //
//*****************************************************************************

void	puterr(char *cmd);
void	no_infile(char *inf_name);

void	init_vars_cm1(t_data *data);
char	*check_cmd(t_data *data);
void	no_cmd_redirs(t_data *data, int *pp0);
void	check_red(char **red);
//*****************************************************************************
//						* B U I L T I N S *									 //
//*****************************************************************************

void	exec_built(t_cmd cm);
int		check_built(char *cmd);
char	*get_oldpwd(char **env);
void	ft_pwd(void);
void	ft_env(void);
void	ft_exit(char **full_cmd);
int		ft_echo(char **the_cmd);
int		ft_cd(char **the_cmd);
void	change_env(char *buf, char *buf2);

int		ft_unset(char **full_cmd);
void	rm_env(int d);

void	copy_env(char **env);
void	copy_env_two(char **env);

//*****************************************************************************
//						* F T _ E X P O R T _ U T I L S *					 //
//*****************************************************************************

void	crea_envexp(void);
void	add_env(char *var);
void	env_exp(char **env);
void	add_env_exp(char *var);
int		check_char_err(char *the_cm);

int		ft_export(char **full_cmd, int k);

void	exec_last_built(t_cmd cm, int fd);

int		ft_unset_one(char *var);
int		ft_unset_xp(char **full_cmd);
int		ft_unset_one_xp(char *var);
int		check_db_xp(char *var);
void	ft_change_exit_status(int x);

//*****************************************************************************
//						* F T _ U N S E T _ U T I L S *						 //
//*****************************************************************************

int		check_db_xp(char *var);
void	check_uns_err(char **full_cmd);
void	rm_env(int d);
void	rm_env_xp(int d);
int		ft_unset_one(char *var);

#endif
