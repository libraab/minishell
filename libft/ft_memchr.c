/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:59:19 by abouhlel          #+#    #+#             */
/*   Updated: 2021/03/30 16:15:37 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*x;
	size_t			i;

	x = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (x[i] == (unsigned char)c)
			return ((void *) x + i);
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>
int main() 
{

    char x[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    const unsigned int size = 10;

    void * y = ft_memchr(x, 50, size);
    printf("%s\n", y);
    y = memchr(x, 50, size);
    printf("%s\n", y);
}*/
