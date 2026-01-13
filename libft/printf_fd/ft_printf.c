/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:57:22 by nfour             #+#    #+#             */
/*   Updated: 2024/06/21 18:44:52 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../stack_string/stack_string.h"


static void ft_check_p(unsigned long nbr, int *count, int fd)
{
	if (nbr == 0)
	{
		*count += write(fd, "(nil)", 5);
	}
	else
	{
		*count += write(fd, "0x", 2);
		ft_put_p_nbr(nbr, count, fd);
	}
}

static void round_double_sstring(t_sstring *sstr)
{
	int i = sstr->size - 1;
	while (i >= 0) {
		if (sstr->data[i] == '.') {
			i--;
			continue;
		}
		if (sstr->data[i] == '9') {
			sstr->data[i] = '0';
		} else {
			sstr->data[i] += 1;
			break;
		}
		i--;
	}
	if (i < 0) {
		push_sstring(sstr, '1');
	}
}


t_sstring double_to_sstring(double nbr, int precision)
{
	t_sstring	sstr = empty_sstring();
	int			int_part = 0;
	double		decimal_part = (double)0;

	/* handle neg */
	if (nbr < 0) {
		push_sstring(&sstr, '-');
		nbr = -nbr;
	}

	/* Store int and double part */
	int_part = (int)nbr;
	decimal_part = nbr - (double)int_part;
	
	/* Store integer part */
	char *tmp = ft_itoa(int_part);
	if (tmp) {
		concat_sstring(&sstr, tmp);
		free(tmp);
	}

	/* Store point and float part */
	if (decimal_part > (double)0.0) {
		push_sstring(&sstr, '.');
		for (int i = 0; i < precision + 1; ++i) {
			decimal_part *= 10;
			push_sstring(&sstr, (int)decimal_part + '0');
			decimal_part -= (int)decimal_part;
		}
	} else {
		push_sstring(&sstr, '.');
		for (int i = 0; i < precision; ++i) {
			push_sstring(&sstr, '0');
		}
	}

	/* Round and pop last value used for rounded */
	if (sstr.data[sstr.size - 1] >= '5') {
		round_double_sstring(&sstr);
	}
	pop_sstring(&sstr);

	return (sstr);
}

static void ft_put_float_double_nbr(double nbr, int *count, int fd)  {
	*count += ft_printf_fd(fd, "%s", double_to_sstring(nbr, 6).data);
}

// static void test(int nb){
// }

static int ft_continue_display(const char *s, int i, va_list params, int fd)
{
	int nb;

	nb  = 0;
	if (s[i] == 'x')
		ft_put_lx_nbr(va_arg(params, unsigned int), &nb, fd);
	else if (s[i] == 'X')
		ft_put_bigx_nbr(va_arg(params, unsigned int), &nb, fd);
	else if (s[i] == 'f')
		ft_put_float_double_nbr(va_arg(params, double), &nb, fd);
	else if (s[i] == 'p')
		ft_check_p(va_arg(params, unsigned long), &nb, fd);
	else
	{
		nb = write(fd, "%", 1);
		nb += ft_putchar_fd(s[i], fd);
	}
	return (nb);
}

static int ft_display(const char *s, int i, va_list params, int fd)
{
	int	count;

	count = 0;
	i++;
	if (s[i] == 'd')
		count = ft_putlnbr(va_arg(params, int), fd);
	else if (s[i] == 's')
		count = ft_putlstr(va_arg(params, char *), fd);
	else if (s[i] == 'c')
		count = ft_putchar_fd(va_arg(params, int), fd);
	else if (s[i] == 'i')
		count = ft_put_i_nbr(va_arg(params, long long int), fd);
	else if (s[i] == 'u')
		ft_put_lu_nbr(va_arg(params, unsigned long), &count, fd);
	else if (s[i] == '%')
	{
		ft_putchar_fd('%', fd);
		count++;
	}
	else
		count += ft_continue_display(s, i, params, fd);
	return (count);
}

static int ft_print_loop(const char *s, va_list params, int big_len, int fd)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			if (s[i + 1] == '\0')
			{
				big_len += write(fd, "%", 1);
				return (big_len);
			}
			big_len += ft_display(s, i, params, fd);
			i++;
		}
		else
		{
			ft_putchar_fd(s[i], fd);
			big_len++;
		}
		i++;
	}
	return (big_len);
}

int	ft_printf_fd(int fd, const char *s, ...)
{
	size_t	big_len;
	va_list	params;

	big_len = 0;
	va_start(params, s);
	big_len = ft_print_loop(s, params, big_len, fd);
	va_end(params);
	return (big_len);
}