/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:58:24 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/10 15:16:39 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	alloc_init(t_data *data)
{
	data->lexer = malloc (sizeof(t_lexer));
	data->token = malloc (sizeof (t_token));
	data->token_tab = malloc (sizeof (t_token));
	data->cmd = NULL;
}

int	ft_check_cmdless_pipe(char *str)
{
	int i;
	int cmd;
	
	i = 0;
	cmd = 0;
	while (str[i] != '\0') 
	{
		if (str[i] == '|')
		{
			if (cmd == 0)
				return(1);
			else
				cmd = 0;
		}
		else if (str[i] != '|' && str[i] != ' ')
		{
			cmd++;
		}
		i++;
	}
	if (cmd == 0)
		return (1);
	return (0);
}
int	ft_count_pipes(char *str)
{
	int i;
	int count;
	char c;
	
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[0] == '|' || str[ft_strlen(str) - 1] == '|' || ft_check_cmdless_pipe(str) == 1)
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

void	ft_free(t_data *data)
{
	if (data->lexer->content != NULL)
		free (data->lexer->content);
	if (data->token->value != NULL)
		free (data->token->value);
	if (data->lexer != NULL)
		free (data->lexer);
	if (data->token != NULL)
		free (data->token);
}

int	main(void)
{
	t_data	*data;
	char	*entry;
	char **content;
	int i ;

	data = malloc(sizeof(t_data));
	alloc_init(data);
	while (1)
	{
		i = 0;
		entry = readline("\033[30;47m[minishell] >\033[0m ");
		if (entry)
		{
			add_history(entry);
			//int tot = ft_count_pipes(entry);
			content = ft_split_pipe(entry, '|');
			// for (int j = 0; j <= tot; j++)
			// 	printf("%s\n", content[j]);
			while (i <= ft_count_pipes(entry))
			{
				data->lexer = init_lexer(data->lexer, content[i]);
				data->token = lexer_get_next_token(data, data->lexer, data->token);
				i++;
			}
			ft_free(data);
			free(entry);
		}
		else
			ft_error();
	}
	return (0);
}
