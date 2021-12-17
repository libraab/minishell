/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:53:14 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/17 12:29:51 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_val(int val1, int val2)
{
	if (val1 && !val2)
		return (1);
	else if (val1 && val2)
		return (2);
	else if (!val1)
		return (0);
	return (-1);
}

static void	ft_switch(char c, int *sq, int *dq)
{
	if (c == '\'')
		*sq = !sq;
	else
		*dq = !dq;
}

char	*ft_change_flous(t_data *data, char *str, int sq, int dq)
{
	int		i;

	i = 0;
	data->newstr = NULL;
	while (str[i])
	{
		i = ft_skip_quote(str, i, dq, sq);
		if (str[i] == '\'' || str[i] == '"')
			ft_switch(str[i], &sq, &dq);
		else if (str[i] == '$' && (str[i + 1] == '?' || str[i + 1] == '$'))
			i++;
		else if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1]
			&& (!dq || (dq && !sq) || (dq && sq)))
		{
			free(data->newstr);
			data->tmp = ft_val(dq, sq);
			if (data->tmp != -1)
				data->newstr = (ft_replace(data, str, i, ft_find_end(str, i + 1, data->tmp)));
			free(str);
			str = ft_strdup(data->newstr);
			if (!dq && data->newstr == NULL)
				break ;
			free(data->newstr);
			data->newstr = NULL;
		}
		if (str[i] != '$')
			i++;
	}
	return (str);
}
