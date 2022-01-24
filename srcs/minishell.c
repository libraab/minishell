/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:58:24 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/24 15:41:21 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_stock_cmd(t_data *d, int i, int j, int k)
{
	d->cmd[d->i].full_cmd = ft_calloc (sizeof(char *), ft_count_arg(d) + 1);
	d->cmd[d->i].redir = ft_calloc (sizeof(char *), ft_count_redir(d) + 1);
	while (i < d->nb)
	{
		if (d->t_tab[i].e_type == 6)
		{
			d->cmd[d->i].cmd = ft_strdup(d->t_tab[i].value);
			d->cmd[d->i].full_cmd[j] = ft_strdup(d->t_tab[i].value);
			j++;
		}
		else if (d->t_tab[i].e_type == 7 || d->t_tab[i].e_type == 5)
		{
			d->cmd[d->i].full_cmd[j] = ft_strdup(d->t_tab[i].value);
			j++;
		}
		else if (d->t_tab[i].e_type < 5)
		{
			d->cmd[d->i].redir[k] = ft_strdup(d->t_tab[i].value);
			k++;
		}
		i++;
	}
	d->i++;
}

void	init_prompt_vars(int *i, char ***content)
{
	*i = 0;
	*content = NULL;
}

int	ft_prompt(char *entry, t_data *data)
{
	char	**content;
	int		i;

	init_prompt_vars(&i, &content);
	add_history(entry);
	ft_check_invalid_chars(entry);
	content = ft_split_pipe(entry, '|');
	data->tot = ft_count_cmd_nbr(content);
	data->cmd = ft_calloc (sizeof(t_cmd), data->tot);
	data->i = 0;
	while (i < data->tot)
	{
		if (!content[i])
			break ;
		init_lexer(data, content[i]);
		lexer_get_next_token(data, &data->lexer);
		ft_stock_cmd(data, 0, 0, 0);
		ft_free_token_tab(data);
		ft_free(data->lexer.content);
		i++;
	}
	free(content);
	ft_free(entry);
	return (1);
}

void	make_exec(char *entry, t_data *data)
{
	int	status;

	g_exe.rs = 1;
	g_exe.inv_cm = 0;
	g_exe.hdc = 0;
	g_exe.forked = 0;
	ft_prompt(entry, data);
	multi_pipex(data, 0, data->tot - 1);
	while (waitpid(-1, &status, 0) > 0)
		;
	// if (g_exe.forked == 1)
	// 	ft_change_exit_status(WEXITSTATUS(status));
	ft_free_cmd_struct(data, 0, 0, 0);
}

int	main(const int ac, const char **av, char **env)
{
	t_data	data;
	char	*entry;

	(void) ac;
	(void) av;
	ft_init_data(&data);
	copy_env(env);
	crea_envexp();
	while (1)
	{
		signal (SIGINT, ft_signals);
		signal (SIGQUIT, ft_signals);
		entry = readline("\033[1;31mMinishell-->\033[0m ");
		if (!entry)
			return (ft_exit_entry());
		if (ft_entry_is_only_sp(entry))
			continue ;
		if (entry)
			make_exec(entry, &data);
	}
	free_tab(g_exe.env);
	free_tab(g_exe.expenv);
	return (0);
}
