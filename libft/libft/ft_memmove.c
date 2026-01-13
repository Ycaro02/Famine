/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:46:20 by nfour             #+#    #+#             */
/*   Updated: 2024/04/11 16:16:05 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_i;
	unsigned char	*src_i;
	size_t			i;

	i = 0;
	dest_i = (unsigned char *)dest;
	src_i = (unsigned char *)src;
	if (dest > src)
	{
		while (n != 0)
		{
			dest_i[n - 1] = src_i[n - 1];
			n--;
		}
	}
	else if (dest < src)
	{
		while (i < n)
		{
			dest_i[i] = src_i[i];
			i++;
		}
	}
	return (dest);
}
