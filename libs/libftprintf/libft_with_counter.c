/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_with_counter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 02:00:27 by dkot              #+#    #+#             */
/*   Updated: 2024/10/28 02:30:44 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_with_counter_fd(char c, int *printed, int fd)
{
	if (fd < 0)
		return ;
	if (write(fd, &c, 1) == -1)
		return ;
	(*printed)++;
}

void	ft_putnbr_with_counter_fd(int n, int *printed, int fd)
{
	char	c;

	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		if (write(fd, "-2147483648", 11) == -1)
			return ;
		*printed = *printed + 11;
		return ;
	}
	if (n < 0)
	{
		if (write(fd, "-", 1) == -1)
			return ;
		(*printed)++;
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_with_counter_fd(n / 10, printed, fd);
	c = (n % 10) + '0';
	if (write(fd, &c, 1) == -1)
		return ;
	(*printed)++;
}

void	ft_putstr_with_counter_fd(char *s, int *printed, int fd)
{
	int	i;

	if (fd < 0)
		return ;
	if (s == NULL)
	{
		if (write(fd, "(null)", 6) == -1)
			return ;
		*printed += 6;
		return ;
	}
	i = 0;
	while (s[i])
	{
		if (write(fd, &s[i], 1) == -1)
			return ;
		(*printed)++;
		i++;
	}
}
