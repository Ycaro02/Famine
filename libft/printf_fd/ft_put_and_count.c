/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_and_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:21:26 by nfour             #+#    #+#             */
/*   Updated: 2022/10/05 15:20:50 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_lu_nbr(unsigned int nbr, int *count, int fd)
{
	if (nbr > 9)
		ft_put_lu_nbr(nbr / 10, count, fd);
	ft_putchar_fd(nbr % 10 + '0', fd);
	(*count)++;
}

void	ft_put_lx_nbr(unsigned int nbr, int *count, int fd)
{
	char	*base_16;

	base_16 = "0123456789abcdef";
	if (nbr > 15)
		ft_put_lx_nbr(nbr / 16, count, fd);
	ft_putchar_fd(base_16[nbr % 16], fd);
	(*count)++;
}

void	ft_put_bigx_nbr(unsigned int nbr, int *count, int fd)
{
	char	*big_base16;

	big_base16 = "0123456789ABCDEF";
	if (nbr > 15)
		ft_put_bigx_nbr(nbr / 16, count, fd);
	ft_putchar_fd(big_base16[nbr % 16], fd);
	(*count)++;
}

void	ft_put_p_nbr(unsigned long nbr, int *count, int fd)
{
	char	*base_16;

	base_16 = "0123456789abcdef";
	if (nbr > 15)
		ft_put_p_nbr(nbr / 16, count, fd);
	ft_putchar_fd(base_16[nbr % 16], fd);
	(*count)++;
}
