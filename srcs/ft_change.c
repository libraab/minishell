/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:53:14 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/17 14:11:42 by abouhlel         ###   ########.fr       */
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
		*sq = !*sq;
	else
		*dq = !*dq;
}

char	*ft_change_flous(t_data *d, char *s, int sq, int dq)
{
	while (s[d->j])
	{
		d->j = ft_skip_quote(s, d->j, dq, sq);
		if (s[d->j] == '\'' || s[d->j] == '"')
			ft_switch(s[d->j], &sq, &dq);
		else if (s[d->j] == '$' && (s[d->j + 1] == '?' || s[d->j + 1] == '$'))
			d->j++;
		else if (s[d->j] == '$' && s[d->j + 1] != ' ' && s[d->j + 1]
			&& (!dq || (dq && !sq) || (dq && sq)))
		{
			free(d->newstr);
			d->tmp = ft_val(dq, sq);
			if (d->tmp != -1)
				d->newstr = (ft_rep(d, s, d->j, ft_end(s, d->j + 1, d->tmp)));
			free(s);
			s = ft_strdup(d->newstr);
			if (!dq && d->newstr == NULL)
				break ;
			free(d->newstr);
			d->newstr = NULL;
		}
		if (s[d->j] != '$')
			d->j++;
	}
	return (s);
}
