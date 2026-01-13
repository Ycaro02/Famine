/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intfunction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:51:54 by nfour             #+#    #+#             */
/*   Updated: 2022/10/05 15:19:15 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_count_digit(int nb)
{
	int			count;
	long long	n;

	n = (long long)nb;
	count = 0;
	if (nb < 0)
	{
		n *= -1;
		count++;
	}
	if (n == 0)
		return (1);
	while (n != 0)
	{
		if (n > 0)
		{
			n /= 10;
			count++;
		}
	}
	return (count);
}

int	ft_putlnbr(int nbr, int fd)
{
	int	count;

	count = ft_count_digit(nbr);
	if (nbr < 0)
	{
		if (nbr == -2147483648)
		{
			write(fd, "-2147483648", 11);
			return (11);
		}
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr / 10 != 0)
		ft_putlnbr(nbr / 10, fd);
	ft_putchar_fd(nbr % 10 + '0', fd);
	return (count);
}

int	ft_putlstr(char *str, int fd)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write (fd, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write (fd, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_put_i_nbr(long long int nbr, int fd)
{
	int				count;
	long long int	nb;

	count = ft_count_digit(nbr);
	nb = (long long int)nbr;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = nb * -1;
	}
	if (nb / 10 != 0)
		ft_put_i_nbr(nb / 10, fd);
	ft_putchar_fd(nb % 10 + '0', fd);
	return (count);
}
