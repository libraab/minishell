/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:18:54 by hboukhor          #+#    #+#             */
/*   Updated: 2021/12/25 12:21:36 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_search_file(char **red, int i)
{
	if (red[i + 1][0] == '\0')
	{
		printf("syntax error near unexpected token '%s'\n", red[i]);
		ft_change_exit_status(258);
		return (0);
	}
	return (1);
}

int	take_redir(char **red, int *inf, int *outf)
{
	int	i;
	int	h;

	i = 0;
	h = 0;
	while (red[i])
	{
		if (!ft_search_file(red, i))
			return (1);
		else if (red[i][0] == '<' && red[i][1] != '<')
			open_inf(red[i + 1], inf);
		else if (red[i][0] == '>' && red[i][1] != '>')
			open_outf(red[i + 1], outf);
		else if (red[i][0] == '>' && red[i][1] == '>')
			open_outf_db(red[i + 1], outf);
		else if (red[i][0] == '<' && red[i][1] == '<' && h == 0)
		{
			hd(red);
			h = 1;
		}
		i += 2;
	}
	return (0);
}
