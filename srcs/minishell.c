/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:58:24 by abouhlel          #+#    #+#             */
/*   Updated: 2021/10/25 10:58:27 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*buf;

	while (1)
	{
		buf = readline("\033[30;47m[minishell] >\033[0m ");
		if (buf)
		{
			printf("\"%s\"\n", buf);
			if (*buf)
				add_history(buf);
			free(buf);
		}
		else
		{
			ft_putendl_fd("Error", 2);
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
