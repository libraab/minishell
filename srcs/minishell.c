/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:58:24 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/17 09:05:51 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_cmd_nbr(char **str)
{
	int	i;
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_count_arg(t_data *data)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	while (i < data->token->nb)
	{
		if (data->token_tab[i]->e_type == 7)
			count++;
		i++;
	}
	return (count);
}

int	ft_count_redir(t_data *data)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	while (i < data->token->nb)
	{
		if (data->token_tab[i]->e_type < 6)
			count++;
		i++;
	}
	return (count);
}

void	ft_stock_cmd(t_data *data)
{
	int	i;
	int	j;
	int	k;
	
	i = 0;
	j = 0;
	k = 0;
	data->cmd[data->cmd_index] = ft_calloc (sizeof(t_cmd), 1);
	data->cmd[data->cmd_index]->full_cmd = ft_calloc (sizeof(char *), ft_count_arg(data) + 1);
	data->cmd[data->cmd_index]->redir = ft_calloc (sizeof(char *), ft_count_redir(data) + 1);
	while (i < data->token->nb)
	{
		if (data->token_tab[i]->e_type == 6)
		{
			data->cmd[data->cmd_index]->cmd = ft_calloc (sizeof(char), ft_strlen(data->token_tab[i]->value) + 1);
			data->cmd[data->cmd_index]->cmd = data->token_tab[i]->value;
		}
		else if (data->token_tab[i]->e_type == 7)
		{
			data->cmd[data->cmd_index]->full_cmd[j] = ft_calloc (sizeof(char), ft_strlen(data->token_tab[i]->value) + 1);
			data->cmd[data->cmd_index]->full_cmd[j] = data->token_tab[i]->value;
			j++;
		}
		else if (data->token_tab[i]->e_type < 6)
		{
			data->cmd[data->cmd_index]->redir[k] = ft_calloc (sizeof(char), ft_strlen(data->token_tab[i]->value) + 1);
			data->cmd[data->cmd_index]->redir[k] = data->token_tab[i]->value;
			k++;
		}
		i++;
	}
	data->cmd_index++;
}

int	ft_prompt(char *entry, char **content, t_data *data, int i)
{
	add_history(entry);
	ft_check_invalid_chars(entry);
	content = ft_split_pipe(entry, '|');
	data->tot = ft_count_cmd_nbr(content);
	data->cmd = ft_calloc (sizeof(t_cmd *), data->tot);
	while (i < data->tot)
	{
		if (!content[i])
			break ;
		init_lexer(data, content[i]);
		lexer_get_next_token(data, data->lexer, data->token);
		ft_stock_cmd(data);
		i++;
	}
	//*******************************************************************************
	// for (int j = 0; j < data->token->nb ; j++)
	// 	printf("[%d][%s]\n", data->token_tab[j]->e_type, data->token_tab[j]->value);
	//*******************************************************************************
	// for (int k = 0; k < data->tot; k++)
	// {
	// 	printf("\n {printing cmd_struct}   \n");
	// 	printf("__________________________\n");
	// 	printf("| cmd        |   [%s]\n", data->cmd[k]->cmd);
	// 	printf("__________________________\n");
	// 	for (int m = 0; data->cmd[k]->full_cmd[m]; m++)
	// 		printf("| full cmd   |   [%s]\n", data->cmd[k]->full_cmd[m]);
	// 	printf("__________________________\n");
	// 	for (int n = 0; data->cmd[k]->redir[n]; n++)
	// 		printf("| redir      |   [%s]\n", data->cmd[k]->redir[n]);
	// 	printf("__________________________\n");
	// }
	printf("%p", data->cmd[0]);
	for (int i = 0; data->cmd[i]; i++)
	{
		printf("| cmd        |   [%s]\n", data->cmd[i]->cmd);
		for (int n = 0; data->cmd[i]->full_cmd[n]; n++)
			printf("| full cmd   |   [%s]\n", data->cmd[i]->full_cmd[n]);
		for (int n = 0; data->cmd[i]->redir[n]; n++)
			printf("| redir      |   [%s]\n", data->cmd[i]->redir[n]);
	}
	//*******************************************************************************
	//ft_free(data);
	free(entry);
	return (1);
}

int	main(void)
{
	int		i ;
	t_data	*data;
	char	*entry;
	char	**content;

	data = ft_calloc (sizeof(t_data), 1);
	while (1)
	{
		ft_alloc_init(data);
		i = 0;
		entry = readline("\033[30;47m[minishell] >\033[0m ");
		if (!entry)
			continue ;
		else if (entry)
			ft_prompt(entry, content, data, i);
		else
			ft_error();
	}
	return (0);
}
