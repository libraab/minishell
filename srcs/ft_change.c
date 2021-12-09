/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:53:14 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/09 15:55:55 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_change_flous(t_data *data, char *str, int sq, int dq)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = NULL;
	while (str[i])
	{
		i = ft_skip_quote(str, i, dq, sq);
		if (str[i] == '\'')
			sq = !sq;
		else if (str[i] == '"')
			dq = !dq;
		else if (str[i] == '$' && (str[i + 1] == '?' || str[i + 1] == '$'))
			i++;
		else if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] && !dq)
		{
			free(newstr);
			newstr = (ft_replace(data, str, i, ft_find_end(str, i + 1, 0)));
			free(str);
			str = ft_strdup(newstr);
			if (newstr == NULL)
				break ;
			free(newstr);
			newstr = NULL;
		}
		else if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] && dq && !sq)
		{
			free(newstr);
			newstr = (ft_replace(data, str, i, ft_find_end(str, i + 1, 1)));
			free(str);
			str = ft_strdup(newstr);
			free(newstr);
			newstr = NULL;
		}
		else if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] && dq && sq)
		{
			free(newstr);
			newstr = (ft_replace(data, str, i, ft_find_end(str, i + 1, 2)));
			free(str);
			str = ft_strdup(newstr);
			free(newstr);
			newstr = NULL;
		}
		i++;
	}
	return (str);
}
