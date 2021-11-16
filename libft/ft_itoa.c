/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:23:46 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/16 09:02:41 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_itoa_size(int n)
{
	int	size;

	size = 0;
	if (n < 0 && n > -2147483648)
	{
		size++;
		n = -n;
	}
	else if (n == 0)
		return (1);
	else if (n == -2147483648)
		return (11);
	while (n >= 1)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static	int	ft_makepos(int x)
{
	if (x < 0)
		return (-x);
	else
		return (x);
}

static	int	ft_isneg(int x)
{
	if (x < 0)
		return (1);
	else
		return (0);
}

char	*ft_itoa(int n)
{
	char			*s;
	int				i;
	int				size;
	int				neg;
	unsigned int	tmp;

	i = 1;
	size = ft_itoa_size(n);
	neg = ft_isneg(n);
	tmp = ft_makepos(n);
	s = (char *)malloc(sizeof(char) * ft_itoa_size(n) + 1);
	if (!s)
		return (NULL);
	if (tmp == 0)
		s[tmp] = '0';
	while (tmp >= 1)
	{
		s[size - i] = (tmp % 10) + '0';
		tmp /= 10;
		i++;
	}
	if (neg)
		*s = '-';
	s[size] = '\0';
	return (s);
}
