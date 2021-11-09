/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:58:24 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/09 19:06:43 by abouhlel         ###   ########.fr       */
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

int	ft_check_double_pipe(char *str)
{
	int i;
	
	i = 0;
	while (str[i] != '\0') 
	{
		if (str[i] == ' ')
			i++;
		else if (str[i] == '|')
			return (1);
		else if (str[i] != '|' && str[i] != ' ')
			return (0); // there is a command between the pipes
	}
	return (1); //in case " cmd |         "
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
		if (str[0] == '|' || str[ft_strlen(str) - 1] == '|' || ft_check_double_pipe(str) == 1)
		{
			printf("ERROR\n");
			exit(EXIT_FAILURE);
		}
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

// void	ft_free(t_data *data)
// {
// 	if (data->lexer->content != NULL)
// 		free (data->lexer->content);
// 	if (data->token->value != NULL)
// 		free (data->token->value);
// 	if (data->lexer != NULL)
// 		free (data->lexer);
// 	if (data->token != NULL)
// 		free (data->token);
// }

int	main(void)
{
	char	*entry;
	t_data	*data;
	char **content;
	int i = 0;

	data = malloc(sizeof(t_data));
	alloc_init(data);
	while (1)
	{
		entry = readline("\033[30;47m[minishell] >\033[0m ");
		if (entry)
		{
			add_history(entry);
			content = ft_split(entry, '|'); //mettre le split custom ici
			while (i <= ft_count_pipes(entry))
			{
				data->lexer = init_lexer(data->lexer, content[i]);
				data->token = lexer_get_next_token(data, data->lexer, data->token);
				i++;
			}
			//ft_free(data);
			free(entry);
		}
		else
		{
			ft_putendl_fd("Error", 2);
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
