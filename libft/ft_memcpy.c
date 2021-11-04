/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:03:03 by abouhlel          #+#    #+#             */
/*   Updated: 2021/03/30 16:15:57 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*origin;

	if (!dst && !src)
		return (NULL);
	origin = dst;
	while (n > 0)
	{
		*((char *)dst) = *((char *)src);
		dst++;
		src++;
		n--;
	}
	return (origin);
}
/*#include <stdio.h>
int main() {

    int array [] = { 54, 85, 20, 63, 21 };
    int * copy = NULL;
    int length = sizeof( int ) * 5;
    int i = 0;   
    copy = (int *) malloc( length );
    ft_memcpy( copy, array, length );
        
    while (i < 5)
	{
        printf( "%d ", copy[i] );
		i++;
    }
    printf( "\n" );
    free( copy );
}*/
