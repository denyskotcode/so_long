/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:22:21 by dkot              #+#    #+#             */
/*   Updated: 2024/09/29 23:03:08 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*u_dest;
	const unsigned char	*u_src;

	if (n == 0)
		return (dest);
	if (!dest || !src)
		return (NULL);
	u_dest = (unsigned char *)dest;
	u_src = (const unsigned char *)src;
	while (n--)
		*u_dest++ = *u_src++;
	return (dest);
}
