/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:18:54 by hboukhor          #+#    #+#             */
/*   Updated: 2021/12/25 12:39:24 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_signals_exec(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		ft_change_exit_status(130);
	}
	if (sig == SIGQUIT)
	{
		printf("Quit: 3\n");
		ft_change_exit_status(131);
	}
}
