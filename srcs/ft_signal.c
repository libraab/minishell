/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:05:41 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/24 19:18:16 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signals(int sig)
{
	if (sig == SIGINT)
	{
		if (g_exe.hdc == 0)
		{
			printf("\e[2K");
			rl_on_new_line();
			rl_redisplay();
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			ft_change_exit_status(1);
		}
		else
			exit(1);
	}
	if (sig == SIGQUIT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
}

int	ft_exit_entry(void)
{
	write(1, "exit\n", 5);
	return (0);
}

int	ft_entry_is_only_sp(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	if (str != NULL)
		free (str);
	return (1);
}

void	ft_init_data(t_data *d)
{
	d->lexer = (t_lexer){0};
	d->cmd = 0;
	d->t_tab = 0;
	d->i = 0;
	d->tot = 0;
	d->nb = 0;
	d->env = 0;
}

void	echo_control_seq(int c)
{
	struct termios	conf;

	ioctl(ttyslot(), TIOCGETA, &conf);
	if (c == 1)
		conf.c_lflag |= ECHOCTL;
	else if (c == 0)
		conf.c_lflag &= ~(ECHOCTL);
	ioctl(ttyslot(), TIOCSETA, &conf);
}
