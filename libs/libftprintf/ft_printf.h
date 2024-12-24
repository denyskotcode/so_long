/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:32:35 by dkot              #+#    #+#             */
/*   Updated: 2024/10/28 02:24:46 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
void	ft_unsigned_decimal_putnbr_fd(unsigned int n, int*printed, int fd);
void	ft_putptr_fd(void *ptr, int*printed, int fd);
void	ft_putchar_with_counter_fd(char c, int*printed, int fd);
void	ft_putnbr_with_counter_fd(int n, int*printed, int fd);
void	ft_putstr_with_counter_fd(char *s, int*printed, int fd);
void	ft_puthexnbr_fd(unsigned long n, char size, int*printed, int fd);

#endif
