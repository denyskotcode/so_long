/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 00:50:11 by dkot              #+#    #+#             */
/*   Updated: 2024/10/29 16:50:47 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen_with_nl(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] && s[len] != '\n')
		len++;
	if (s[len] == '\n')
		len++;
	return (len);
}

char	*process_remainder(char **remainder)
{
	char	*line;
	char	*new_remainder;
	size_t	len;

	if (*remainder && ft_strchr(*remainder, '\n'))
	{
		len = ft_strlen_with_nl(*remainder);
		line = ft_substr(*remainder, 0, len);
		new_remainder = ft_strdup(*remainder + len);
		free(*remainder);
		*remainder = new_remainder;
		return (line);
	}
	if (*remainder && **remainder)
	{
		line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
		return (line);
	}
	free(*remainder);
	*remainder = NULL;
	return (NULL);
}

static int	read_into_remainder(int fd, char **remainder)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(*remainder, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*remainder, buffer);
		free(*remainder);
		*remainder = temp;
		if (!*remainder)
			break ;
	}
	free(buffer);
	if (bytes_read < 0 || *remainder == NULL)
		return (-1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*remainders[FD_MAX];
	char		*line;
	int			status;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FD_MAX)
		return (NULL);
	status = read_into_remainder(fd, &remainders[fd]);
	if (status == -1)
	{
		free(remainders[fd]);
		remainders[fd] = NULL;
		return (NULL);
	}
	if (!remainders[fd] || !*remainders[fd])
	{
		free(remainders[fd]);
		remainders[fd] = NULL;
		return (NULL);
	}
	line = process_remainder(&remainders[fd]);
	return (line);
}
