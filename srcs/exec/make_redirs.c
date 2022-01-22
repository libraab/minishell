/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:18:54 by hboukhor          #+#    #+#             */
/*   Updated: 2022/01/22 12:26:50 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_inf(char *infile_name, int *inf)
{
	*inf = open(infile_name, O_RDWR, 0644);
	if (*inf == -1)
		no_infile(infile_name);
	dup2(*inf, STDIN_FILENO);
	close(*inf);
	return (0);
}

int	open_outf(char *outfil_nam, int *outf)
{
	*outf = open(outfil_nam, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(*outf, STDOUT_FILENO);
	close(*outf);
	return (0);
}

void	open_outf_db(char *outfil_nam, int *outf)
{
	*outf = open(outfil_nam, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(*outf, STDOUT_FILENO);
	close(*outf);
	return ;
}

void	make_hd(char **line, int op)
{
	free(*line);
	*line = NULL;
	close(op);
	op = open("tmp", O_RDONLY);
	dup2(op, STDIN_FILENO);
	close(op);
	unlink("tmp");
}

void	hd(char **red)
{
	char	*line;
	int		i;
	int		op;

	i = 0;
	signal(SIGINT, ft_signals);
	while (red[i])
	{
		if (red[i][0] == '<' && red[i][1] == '<')
		{
			op = open("tmp", O_RDWR | O_CREAT | O_TRUNC, 0777);
			if (op == -1)
				puterr("");
			while (1)
			{
				g_exe.hdc = 1;
				echo_control_seq(0);
				line = readline("> ");
				if (!line || !ft_strncmp(line, red[i + 1],
						(ft_strlen(red[i + 1]) + 1)))
					break ;
				write(op, line, ft_strlen(line));
				write(op, "\n", 1);
			}
			g_exe.hdc = 0;
		}
		i += 2;
	}
	make_hd(&line, op);
}
