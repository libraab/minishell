/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:58:24 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/29 11:29:17 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//static int	g_exit_status;

void	ft_signals(int sig)
{
	if (sig == SIGINT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
}

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

int	ft_prompt(char *entry, t_data *data)
{
	char	**content;
	int		i;

	i = 0;
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
		lexer_get_next_token(data, data->lexer);
		ft_stock_cmd(data, 0, 0, 0);
		if (data->lexer->content != NULL)
			free (data->lexer->content);
		i++;
	}
	//****************************************************************
	// printf("\n{MY TOKENS}\n");
	// for (int j = 0; j < data->nb ; j++)
	// 	printf("[%d][%s]\n", data->t_tab[j].e_type, data->t_tab[j].value);
	// //******************************************************************
	// for (int k = 0; k < data->tot; k++)
	// {
	// 	printf("\n         {C M D}   \n");
	// 	printf("_________________________\n");
	// 	printf("| cmd        |   [%s]\n", data->cmd[k].cmd);
	// 	printf("_________________________\n");
	// 	for (int n = 0; data->cmd[k].full_cmd[n]; n++)
	// 		printf("| full cmd   |   [%s]\n", data->cmd[k].full_cmd[n]);
	// 	printf("_________________________\n");
	// 	for (int m = 0; data->cmd[k].redir[m]; m++)
	// 		printf("| redir      |   [%s]\n", data->cmd[k].redir[m]);
	// 	printf("_________________________\n");
	// }
	//*****************************************************************
	//ft_free(data);
	free(entry);
	return (1);
}

int	main(const int ac, const char **av, const char **envp)
{
	t_data	*data;
	char	*entry;

	(void) ac;
	(void) av;
	data = ft_calloc (sizeof(t_data), 1);
	data->env = (char **)envp;
	while (1)
	{
		signal (SIGINT, ft_signals);
		signal (SIGQUIT, ft_signals);
		ft_alloc_init(data);
		entry = readline("\033[30;47m[minishell] >\033[0m ");
		if (!entry)
		{
			write(1, "exit\n", 4);
			return (0);
		}
		if (ft_entry_is_only_sp(entry))
		{
			free (data->lexer);
			free (entry);
			continue ;
		}
		if (entry)
			ft_prompt(entry, data);
		free (data->lexer);
	}
	return (0);
}
