/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 01:27:31 by dkot              #+#    #+#             */
/*   Updated: 2024/10/28 02:26:49 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthexnbr_fd(unsigned long n, char size, int *printed, int fd)
{
	char	c;

	if (n >= 16)
		ft_puthexnbr_fd(n / 16, size, printed, fd);
	n = n % 16;
	if (n >= 10)
	{
		if (size == 'X')
			c = 'A' + (n - 10);
		else
			c = 'a' + (n - 10);
	}
	else
		c = '0' + n;
	if (write(fd, &c, 1) == -1)
		return ;
	(*printed)++;
}
