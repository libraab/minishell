/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:17:55 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/16 09:00:19 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		x;
	int		i;

	x = 0;
	while (s1[x])
		x++;
	str = (char *)malloc(sizeof(char) * (x + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < x)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*int main()
{
	char a[] = "you rock baby";
	char *p = ft_strdup(a);
	char *g = strdup(a);
	printf("%s\n", p);
	printf("%s", g);
}*/
