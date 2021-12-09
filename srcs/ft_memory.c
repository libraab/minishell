/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:35:43 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/09 14:05:35 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_token_tab(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb)
	{
		if (data->t_tab[i].value != NULL)
			free (data->t_tab[i].value);
		i++;
	}
	free (data->t_tab);
}

void	ft_free_content(char **content)
{
	int	i;

	i = 0;
	if (content)
		free(content);
}

void	ft_free_cmd_struct(t_data *data, int i, int j, int k)
{
	while (i < data->tot)
	{
		j = 0;
		if (data->cmd[i].cmd)
			free (data->cmd[i].cmd);
		while (data->cmd[i].full_cmd[j])
		{
			if (data->cmd[i].full_cmd[j])
				free (data->cmd[i].full_cmd[j]);
			j++;
		}
		free (data->cmd[i].full_cmd);
		if (data->cmd[i].redir != NULL)
		{
			k = 0;
			while (data->cmd[i].redir[k])
			{
				free (data->cmd[i].redir[k]);
				k++;
			}
			free (data->cmd[i].redir);
		}
		i++;
	}
	free (data->cmd);
}

void	ft_free_data_env(char **data_env)
{
	int	i;
	int	j;

	i = 0;
	j = ft_count_tab(data_env);
	while (i < j)
	{
		if (data_env[i])
			free (data_env[i]);
		i++;
	}
	free(data_env);
}

char	*ft_free_things(char *env, char *env_var, char *dol_value, int dol_len)
{
	free (dol_value);
	if (env_var != NULL)
	{
		env = ft_strdup(env_var + dol_len);
		free (env_var);
	}
	else
		env = NULL;
	return (env);
}
