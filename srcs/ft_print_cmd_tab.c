/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_cmd_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 09:48:20 by abouhlel          #+#    #+#             */
/*   Updated: 2021/12/17 09:58:33 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_cmd_tab(t_data *data, int i, int j, int k)
{
	i = 0;
	while (i < data->tot)
	{
		printf("\n         {C M D}   \n");
		printf("_________________________\n");
		printf("| cmd        |   [%s]\n", data->cmd[i].cmd);
		printf("_________________________\n");
		j = 0;
		while (data->cmd[i].full_cmd[j])
		{
			printf("| full cmd   |   [%s]\n", data->cmd[i].full_cmd[j]);
			j++;
		}
		printf("_________________________\n");
		k = 0;
		while (data->cmd[i].redir[k])
		{
			printf("| redir      |   [%s]\n", data->cmd[i].redir[k]);
			k++;
		}
		printf("_________________________\n");
		i++;
	}
}
