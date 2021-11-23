/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:58:24 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/23 11:39:54 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_stock_cmd(t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	data->cmd[data->cmd_index].full_cmd = ft_calloc (sizeof(char *), ft_count_arg(data) + 1);
	data->cmd[data->cmd_index].redir = ft_calloc (sizeof(char *), ft_count_redir(data) + 1);
	while (i < data->nb)
	{
		if (data->token_tab[i].e_type == 6)
		{
			data->cmd[data->cmd_index].cmd = ft_strdup(data->token_tab[i].value);
			data->cmd[data->cmd_index].full_cmd[j] = ft_strdup(data->token_tab[i].value);
			j++;
		}
		else if (data->token_tab[i].e_type == 7 || data->token_tab[i].e_type == 5)
		{
			data->cmd[data->cmd_index].full_cmd[j] = ft_strdup(data->token_tab[i].value);
			j++;
		}
		else if (data->token_tab[i].e_type < 5)
		{
			data->cmd[data->cmd_index].redir[k] = ft_strdup(data->token_tab[i].value);
			k++;
		}
		i++;
	}
	data->cmd_index++;
}

int	ft_prompt(char *entry, char **content, t_data *data)
{
	int	i;

	i = 0;
	add_history(entry);
	ft_check_invalid_chars(entry);
	content = ft_split_pipe(entry, '|');
	data->tot = ft_count_cmd_nbr(content);
	data->cmd = ft_calloc (sizeof(t_cmd), data->tot);
	data->cmd_index = 0;
	while (i < data->tot)
	{
		if (!content[i])
			break ;
		init_lexer(data, content[i]);
		lexer_get_next_token(data, data->lexer);
		ft_stock_cmd(data);
		if (data->lexer->content != NULL)
			free (data->lexer->content);
		i++;
	}
	//*******************************************************************************
	// printf("\n{MY TOKENS}\n");
	// for (int j = 0; j < data->nb ; j++)
	// 	printf("[%d][%s]\n", data->token_tab[j].e_type, data->token_tab[j].value);
	//*******************************************************************************
	for (int k = 0; k < data->tot; k++)
	{
		printf("\n         {C M D}   \n");
		printf("_________________________\n");
		printf("| cmd        |   [%s]\n", data->cmd[k].cmd);
		printf("_________________________\n");
		for (int n = 0; data->cmd[k].full_cmd[n]; n++)
			printf("| full cmd   |   [%s]\n", data->cmd[k].full_cmd[n]);
		printf("_________________________\n");
		for (int m = 0; data->cmd[k].redir[m]; m++)
			printf("| redir      |   [%s]\n", data->cmd[k].redir[m]);
		printf("_________________________\n");
	}
	//*******************************************************************************
	ft_free(data);
	free(entry);
	return (1);
}

int	main(void)
{
	t_data	*data;
	char	*entry;
	char	**content;

	content = NULL;
	data = ft_calloc (sizeof(t_data), 1);
	while (1)
	{
		ft_alloc_init(data);
		entry = readline("\033[30;47m[minishell] >\033[0m ");
		if (!entry || ft_entry_is_only_sp(entry))
			continue ;
		else if (entry)
			ft_prompt(entry, content, data);
		else
			ft_error();
	}
	return (0);
}
