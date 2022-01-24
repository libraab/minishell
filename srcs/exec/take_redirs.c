/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:18:54 by hboukhor          #+#    #+#             */
/*   Updated: 2022/01/24 19:35:08 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	red_err(void)
{
	printf("syntax error near unexpected token 'newline'\n");
	ft_change_exit_status(258);
	g_exe.rs = 0;
}

int	check_red2(char **red)
{
	int	i;

	if (red[0] != NULL)
	{
		if (red[1][0] == '\0')
		{
			red_err();
			return (0);
		}
		i = 3;
		if (red[2] != NULL)
		{
			while (i <= tab_len(red))
			{
				if (red[i][0] == '\0')
				{
					red_err();
					return (0);
				}
				i += 2;
			}
		}
	}
	return (1);
}

int	take_redir(char **red, int *inf, int *outf)
{
	int	i;
	int	h;

	i = 0;
	h = 0;
	if (!check_red2(red))
		return (0);
	while (red[i])
	{
		if (red[i][0] == '<' && red[i][1] != '<')
			open_inf(red[i + 1], inf);
		else if (red[i][0] == '>' && red[i][1] != '>')
			open_outf(red[i + 1], outf);
		else if (red[i][0] == '>' && red[i][1] == '>')
			open_outf_db(red[i + 1], outf);
		else if (red[i][0] == '<' && red[i][1] == '<')
			hd(red);
		i += 2;
	}
	return (0);
}
