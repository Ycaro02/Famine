/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:40:26 by nfour             #+#    #+#             */
/*   Updated: 2024/12/30 13:48:13 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

u64 array_to_uint32(const char *nptr)
{
	int				i = 0;
	u64		tmp = 0;

	if (!nptr || !(*nptr)) {
		return (OUT_OF_UINT32);
	}
	while (ft_isdigit(nptr[i]) != 0) {
		tmp *= 10;
		if (tmp > UINT32_MAX) {
			return (OUT_OF_UINT32);
		}
		tmp += nptr[i++] - 48;
	}
	if (nptr[i] != '\0' || tmp > UINT32_MAX) {
		tmp = OUT_OF_UINT32;
	}
	return (tmp);
}

int     ft_atoi(const char *nptr)
{
        int                             i;
        long long int   sign;
        long long int   tmp;

        sign = 1;
        tmp = 0;
        i = 0;
        while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
                i++;
        if (nptr[i] == '-' || nptr[i] == '+')
        {
                if (nptr[i] == '-')
                        sign *= -1;
                i++;
        }
        while (ft_isdigit(nptr[i]) != 0)
        {
                if (tmp * sign < -2147483648)
                        return (0);
                else if (tmp * sign > 2147483647)
                        return (-1);
                tmp *= 10;
                tmp += nptr[i++] - 48;
        }
        return (tmp * sign);
}