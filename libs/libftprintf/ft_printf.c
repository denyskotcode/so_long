/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 01:57:22 by dkot              #+#    #+#             */
/*   Updated: 2024/10/28 02:22:48 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	format_func(char a, int *printed, va_list args)
{
	if (a == 'c')
		ft_putchar_with_counter_fd((char)va_arg(args, int), printed, 1);
	else if (a == 'd' || a == 'i')
		ft_putnbr_with_counter_fd((int)va_arg(args, int), printed, 1);
	else if (a == 's')
		ft_putstr_with_counter_fd(va_arg(args, char *), printed, 1);
	else if (a == 'u')
		ft_unsigned_decimal_putnbr_fd(va_arg(args, unsigned int), printed, 1);
	else if (a == '%')
		ft_putchar_with_counter_fd('%', printed, 1);
	else if (a == 'x')
		ft_puthexnbr_fd(va_arg(args, unsigned int), 'x', printed, 1);
	else if (a == 'X')
		ft_puthexnbr_fd(va_arg(args, unsigned int), 'X', printed, 1);
	else if (a == 'p')
		ft_putptr_fd(va_arg(args, void *), printed, 1);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		printed;

	va_start(args, format);
	i = 0;
	printed = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			i++;
			format_func(format[i], &printed, args);
		}
		else if (format[i] != '%')
		{
			if (write(1, &format[i], 1) != -1)
				printed++;
		}
		else if (format[i] == '%' && format[i + 1] == '\0')
			break ;
		i++;
	}
	va_end(args);
	return (printed);
}
