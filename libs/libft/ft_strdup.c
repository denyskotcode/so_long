/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:55:07 by dkot              #+#    #+#             */
/*   Updated: 2024/09/29 21:00:39 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*ns;
	size_t	i;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	ns = (char *)malloc((sizeof(char) * (len + 1)));
	if (ns == NULL)
		return (NULL);
	i = 0;
	while (len--)
	{
		ns[i] = s[i];
		i++;
	}
	ns[i] = '\0';
	return (ns);
}
