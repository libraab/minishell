/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 09:34:44 by abouhlel          #+#    #+#             */
/*   Updated: 2021/10/11 17:18:07 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (ft_strlen(s) < start)
	{
		newstr = ft_calloc(sizeof(char), 1);
		if (!newstr)
			return (NULL);
		return (newstr);
	}
	if (ft_strlen(s + start) > len)
		newstr = ft_calloc(sizeof(char), len + 1);
	else
		newstr = ft_calloc(sizeof(char), (len - start) + 1);
	if (!newstr)
		return (NULL);
	ft_strncpy(newstr, s + start, len);
	return (newstr);
}
