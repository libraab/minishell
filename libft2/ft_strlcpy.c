/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 09:20:58 by abouhlel          #+#    #+#             */
/*   Updated: 2021/03/30 16:19:22 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	if (!dstsize)
		return (ft_strlen(src));
	if (dstsize > 0)
	{
		i = 0;
		while (src[i] && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
/*
#include <stdio.h>
int	main (void)
{
	char a[] = "Coucouc";
	char b[] = "hola";
	int x = 2;
	printf("%zu\n", ft_strlcpy(a, b, x));
	printf("%s\n\n", a);
	printf("%zu\n", strlcpy(a, b, x));
	printf("%s\n", a);
}
*/