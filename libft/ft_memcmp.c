/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:03:06 by abouhlel          #+#    #+#             */
/*   Updated: 2021/03/30 16:15:46 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*x;
	unsigned char	*y;
	size_t			i;

	x = (unsigned char *)s1;
	y = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (x[i] != y[i])
			return (x[i] - y[i]);
		i++;
	}
	return (0);
}
/*#include <stdio.h>
int main()
{

    int  array1 [] = { 50, 85, 20, 63, 21 };
    int array2 [] = { 50, 85, 20, 63, 20 };
    size_t size = sizeof( int ) * 5;

	printf("%d\n", ft_memcmp( array1, array2, size));
    printf("%d\n", memcmp( array1, array2, size));
    char  array3 [] = { 50, 85, 20, 63, 21 };
    char array4 [] = { 54, 85, 19, 63, 21 };
	printf("%d", strcmp(array3, array4));
}*/
