/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:03:03 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/29 14:06:40 by abouhlel         ###   ########.fr       */
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
