/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:53:42 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/16 09:06:37 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_isneg(int x)
{
	if (x == 1)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long int	a;
	int					i;
	int					b;

	a = 0;
	b = 1;
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\f'
		|| str[i] == '\v' || str[i] == '\t' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			b = b * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = a * 10 + (str[i] - 48);
		i++;
		if (a >= 922337203685477587)
			return (ft_isneg(b));
	}
	return (a * b);
}
