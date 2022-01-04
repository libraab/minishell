/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:35:43 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/25 15:15:12 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_token_tab(t_data *data)
{
	int	i;

	i = 0;
	if (!data || !data->t_tab)
		return ;
	while (i < data->nb)
	{
		if (data->t_tab[i].value)
		{
			free (data->t_tab[i].value);
			data->t_tab[i].value = NULL;
		}
		i++;
	}
	if (data->t_tab)
	{
		free(data->t_tab);
		data->t_tab = NULL;
	}
}

void	ft_free(char *ptr)
{
	if (ptr && *ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	ft_free_double(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i])
	{
		if (tabl[i] != NULL)
		{
			ft_free(tabl[i]);
			i++;
		}
	}
	ft_free(*tabl);
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

char	*ft_free_things(char *env, char *env_var, char *dolv, int len)
{
	free (dolv);
	if (env_var != NULL)
	{
		env = ft_strdup(env_var + len);
		free (env_var);
	}
	else
		env = NULL;
	return (env);
}
