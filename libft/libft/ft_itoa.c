/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:03:40 by nfour             #+#    #+#             */
/*   Updated: 2024/04/11 16:16:05 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_make(long int n, char *dst, int count, int sign)
{
	if (n == 0)
	{
		dst = ft_calloc(sizeof(char), 2);
		dst[0] = '0';
		dst[1] = '\0';
		return (dst);
	}
	dst = ft_calloc(sizeof(char), count + 1);
	if (dst == NULL)
		return (NULL);
	count--;
	while (count >= sign)
	{
		dst[count] = (n % 10) + 48;
		n /= 10;
		count--;
	}
	if (sign == 1)
		dst[0] = '-';
	return (dst);
}

char	*ft_itoa(int n)
{
	int			count;
	char		*dst;
	long int	tmp;
	int			sign;	
	long int	nbr;

	dst = NULL;
	nbr = (long int)n;
	sign = 0;
	count = 0;
	if (nbr < 0)
	{
		nbr = (long int)n * -1;
		sign = 1;
		count++;
	}
	tmp = nbr;
	while (tmp != 0)
	{
		tmp /= 10;
		count++;
	}
	dst = ft_make(nbr, dst, count, sign);
	return (dst);
}
