/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:58:24 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/15 19:28:25 by abouhlel         ###   ########.fr       */
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

int	ft_prompt(char *entry, char **content, t_data *data, int i)
{
	add_history(entry);
	ft_check_invalid_chars(entry);
	content = ft_split_pipe(entry, '|');
	data->tot = ft_count_pipes(entry) + 1;
	data->cmd = ft_calloc (sizeof (t_cmd), data->tot);
	while (i < data->tot)
	{
		if (!content[i])
			break ;
		init_lexer(data, content[i]);
		lexer_get_next_token(data, data->lexer, data->token);
		i++;
	}
	// for (int j = 0; j < data->token->nb ; j++)
	// 	printf("[%d][%s]\n", data->token_tab[j]->e_type,
	// 	data->token_tab[j]->value);
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
