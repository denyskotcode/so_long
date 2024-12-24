/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal_unsigned_int.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 01:32:20 by dkot              #+#    #+#             */
/*   Updated: 2024/10/28 01:53:59 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_unsigned_decimal_putnbr_fd(unsigned int n, int*printed, int fd)
{
	char	c;

	if (n >= 10)
		ft_unsigned_decimal_putnbr_fd(n / 10, printed, fd);
	c = (n % 10) + '0';
	if (write(fd, &c, fd) == -1)
		return ;
	(*printed)++;
}
