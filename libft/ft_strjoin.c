/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 09:20:00 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/16 09:00:22 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*all;

	if (!s1 || !s2)
		return (NULL);
	all = malloc (sizeof (char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!all)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		all[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		all[i + j] = s2[j];
		j++;
	}
	all[i + j] = '\0';
	return (all);
}
/*int main()
{
	char a[] = "anticonsti";
	char b[] = "tutionnellement";
	printf("%s", ft_strjoin(a, b));
}*/
