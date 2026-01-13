/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:55:02 by nfour             #+#    #+#             */
/*   Updated: 2024/06/21 18:46:07 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "../libft.h"

void	ft_put_lu_nbr(unsigned int nbr, int *count, int fd);
int		ft_count_digit(int nb);
int		ft_putlnbr(int nbr, int fd);
int		ft_putlstr(char *str, int fd);
int		ft_put_i_nbr(long long int nbr, int fd);
int		ft_printf_fd(int fd, const char *s, ...);
void	ft_put_lx_nbr(unsigned int nbr, int *count, int fd);
void	ft_put_bigx_nbr(unsigned int nbr, int *count, int fd);
void	ft_put_p_nbr(unsigned long nbr, int *count, int fd);

t_sstring double_to_sstring(double nbr, int precision);

#endif
