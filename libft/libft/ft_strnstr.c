/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:09:26 by nfour             #+#    #+#             */
/*   Updated: 2024/04/11 16:16:05 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		little_len;

	little_len = ft_strlen(little);
	i = 0;
	if (big == NULL && len == 0)
		return (NULL);
	if (little_len == 0)
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		if (ft_strncmp(&big[i], &little[0], little_len) == 0
			&& i + little_len - 1 < len)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
