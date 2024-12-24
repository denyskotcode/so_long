/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:52:37 by dkot              #+#    #+#             */
/*   Updated: 2024/09/29 20:49:39 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	temp_c;
	unsigned char	*temp_s;

	if (!s)
		return (NULL);
	temp_c = (unsigned char)c;
	temp_s = (unsigned char *)s;
	while (n--)
		*temp_s++ = temp_c;
	return (s);
}
