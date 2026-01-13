/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:00:04 by nfour             #+#    #+#             */
/*   Updated: 2024/04/11 16:16:05 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	size;

	if (s == NULL)
		return (NULL);
	size = ft_strlen(s) - start;
	if ((size_t)start >= ft_strlen(s))
	{
		dest = ft_calloc(sizeof(char), 1);
		return (dest);
	}
	if ((start + len) > size)
	{	
		dest = ft_calloc(sizeof(char), size + 1);
		if (dest == NULL)
			return (NULL);
		ft_strlcpy(dest, &s[start], len + 1);
		return (dest);
	}
	else
		dest = ft_calloc(sizeof(char), len + 1);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, &s[start], len + 1);
	return (dest);
}
