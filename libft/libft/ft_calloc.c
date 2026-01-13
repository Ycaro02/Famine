/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:29:32 by nfour             #+#    #+#             */
/*   Updated: 2024/04/11 16:16:05 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int				nb;
	unsigned char	*array;

	nb = (nmemb * size);
	if (nmemb != 0 && nb / nmemb != size)
		return (NULL);
	if (nmemb == 0 || size == 0)
	{
		array = (unsigned char *)malloc(sizeof(char) * 1);
		array[0] = '\0';
		return (array);
	}
	array = (unsigned char *)malloc(nmemb * size);
	if (array == NULL)
		return (NULL);
	ft_bzero(array, (nmemb * size));
	return ((void *)array);
}
