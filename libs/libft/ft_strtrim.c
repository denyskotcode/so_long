/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:20:55 by dkot              #+#    #+#             */
/*   Updated: 2024/09/29 20:03:37 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first;
	size_t	last;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	first = 0;
	last = ft_strlen(s1);
	while (s1[first] && ft_strchr(set, s1[first]))
		first++;
	while (first < last && ft_strchr(set, s1[last - 1]))
		last--;
	if (last < first)
		return (NULL);
	result = malloc(sizeof(char) * (last - first + 1));
	if (!result)
		return (NULL);
	ft_memcpy(result, s1 + first, last - first);
	result[last - first] = '\0';
	return (result);
}
