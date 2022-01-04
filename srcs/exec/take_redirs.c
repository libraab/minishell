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

//void	redir_err
int	take_redir(char **red, int *inf, int *outf)
{
	int	i;
	int	h;

	i = 0;
	h = 0;
	while (red[i])
	{
		if (red[i + 1][0] == '\0')
		{
			printf("syntax error near unexpected token '%s'\n", red[i]);
			exe.stat = 2;
			return (1);
		}
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
//unset hd middle 