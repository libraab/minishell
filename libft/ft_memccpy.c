/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:59:03 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/16 08:59:29 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*x;
	unsigned char	*y;
	unsigned char	a;

	a = (unsigned char)c;
	x = (unsigned char *)dst;
	y = (unsigned char *)src;
	while (n)
	{
		*x = *y;
		x++;
		n--;
		if (*y == a)
			return (x);
		y++;
	}
	return (NULL);
}
