/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:59:03 by abouhlel          #+#    #+#             */
/*   Updated: 2021/03/30 16:56:57 by abouhlel         ###   ########.fr       */
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
/*#include <stdio.h>
int main()
{
	const char * text = "bla bla bla. bidule";
	size_t len = ft_strlen(text);

	char y[len];
	char * res = ft_memccpy(y, text, '.', len);

	if (res != NULL)
	{
		printf("%s\n", y);
	}
	else
	{
        	printf( "nothing\n" );
	}
	return EXIT_SUCCESS;
}*/
