/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:58:24 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/16 10:43:22 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_pipes(char *str)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[0] == '|' || str[ft_strlen(str) - 1] == '|')
			ft_error();
		if (ft_check_cmdless_pipe(str) == 1)
			ft_error();
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			while (str[i] != c)
				i++;
		}
		if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
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

void	ft_stock_cmd(t_data *data)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	data->cmd[data->cmd_index] = ft_calloc (sizeof(t_cmd), 1);
	while (i < data->token->nb)
	{
		if (data->token_tab[i]->e_type == 6)
		{
			data->cmd[data->cmd_index]->cmd = ft_calloc (sizeof(char), ft_strlen(data->token_tab[i]->value));
			data->cmd[data->cmd_index]->cmd = data->token_tab[i]->value;
		}
		if (data->token_tab[i]->e_type == 7)
		{
			data->cmd[data->cmd_index]->full_cmd = ft_calloc (sizeof(char *), ft_count_arg(data) + 1);
			while (j < ft_count_arg(data))
			{
				data->cmd[data->cmd_index]->full_cmd[j] = ft_calloc (sizeof(char), ft_strlen(data->token_tab[i]->value));
				data->cmd[data->cmd_index]->full_cmd[j] = data->token_tab[i]->value;
				j++;
				i++;
			}
		}
		if (data->token_tab[i]->e_type >= 0 && data->token_tab[i]->e_type < 6)
		{
			
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
	data->tot = ft_count_pipes(entry) + 1;
	data->cmd = ft_calloc (sizeof (t_cmd), data->tot);
	data->cmd_index = 0;
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
	for (int j = 0; j < data->token->nb ; j++)
		printf("[%d][%s]\n", data->token_tab[j]->e_type, data->token_tab[j]->value);
	//*******************************************************************************
	ft_free(data);
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
		if (entry)
			ft_prompt(entry, content, data, i);
		else
			ft_error();
	}
	return (0);
}
