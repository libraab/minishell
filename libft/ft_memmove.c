/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:59:55 by abouhlel          #+#    #+#             */
/*   Updated: 2021/03/30 16:16:04 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*x;
	unsigned char	*y;

	if (!dst && !src)
		return (NULL);
	i = 0;
	x = (unsigned char *)dst;
	y = (unsigned char *)src;
	if ((x > y) && y < (x + len))
	{
		while (i < len)
		{
			x[len - 1] = y[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(x, y, len);
	return ((void *)x);
}
/*#include <stdio.h>
int main()
{
	char a[] = "hellodljdlsjhlj";
	char b[] = "bo";
	printf("%s\n", ft_memmove(a, b, 8));
	printf("%s", memmove(a, b, 8));
}*/
