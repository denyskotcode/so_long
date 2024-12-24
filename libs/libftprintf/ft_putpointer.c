/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 01:17:29 by dkot              #+#    #+#             */
/*   Updated: 2024/10/28 02:00:11 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptr_fd(void *ptr, int*printed, int fd)
{
	unsigned long	point;

	if (ptr == NULL)
	{
		ft_putstr_with_counter_fd("(nil)", printed, fd);
		return ;
	}
	point = (unsigned long)ptr;
	ft_putstr_with_counter_fd("0x", printed, fd);
	ft_puthexnbr_fd(point, 'x', printed, fd);
}
