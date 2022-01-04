/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:58:31 by abouhlel          #+#    #+#             */
/*   Updated: 2021/11/24 09:23:14 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_the_two_str(char *s1, char *s2)
{
	if (s1 && *s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2 && *s2)
	{
		free(s2);
		s2 = NULL;
	}
}

char	*ft_strcat(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	newstr = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		newstr[i] = s2[j];
		i++;
		j++;
	}
	newstr[i] = '\0';
	ft_free_the_two_str(s1, s2);
	return (newstr);
}
