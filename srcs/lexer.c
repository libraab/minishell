/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:01:58 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/17 13:30:05 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_token(t_data *data, int type, char *value)
{
	t_token	*tmp;
	int		j;

	j = 0;
	tmp = ft_calloc(sizeof(t_token), (data->nb + 1));
	while (j < data->nb)
	{
		tmp[j].e_type = data->t_tab[j].e_type;
		tmp[j].value = ft_strdup(data->t_tab[j].value);
		j++;
	}
	tmp[j].e_type = type;
	tmp[j].value = ft_strdup(value);
	if (data->t_tab != NULL)
		ft_free_token_tab(data);
	data->t_tab = tmp;
	data->nb++;
}

int	init_lexer(t_data *data, char *content)
{
	data->lexer.index = 0;
	data->nb = 0;
	data->t_tab = NULL;
	data->newstr = NULL;
	data->j = 0;
	data->lexer.content = ft_change_flous(data, content, 0, 0);
	if (data->lexer.content == NULL)
		return (0);
	data->lexer.c = data->lexer.content[0];
	return (1);
}

int	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->index < ft_strlen(lexer->content))
	{
		lexer->index++;
		lexer->c = lexer->content[lexer->index];
		return (1);
	}
	return (0);
}

int	ft_count_tab(char **tableau)
{
	int	i;

	i = 0;
	while (tableau[i])
		i++;
	return (i);
}

char	**ft_clone_env(char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = ft_calloc(sizeof(char *), ft_count_tab(env) + 1);
	while (i < ft_count_tab(env))
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	return (new_env);
}
