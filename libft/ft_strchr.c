/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:17:36 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/16 09:00:11 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char )c)
		return ((char *) s + i);
	return (NULL);
}
/*#include <stdio.h>
int main()
{
	char a[] ="hell world";
	int c = '5';
	printf("%s\n\n", ft_strchr(a, c));
	printf("%s", strchr(a, c));
}*/
