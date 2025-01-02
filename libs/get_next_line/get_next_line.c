/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 06:05:40 by dkot              #+#    #+#             */
/*   Updated: 2025/01/02 06:10:25 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*g_stored = NULL;

void	free_gnl_buffer(void)
{
	if (g_stored)
	{
		free(g_stored);
		g_stored = NULL;
	}
}

static char	*extract_line(const char *stored)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!stored || !stored[0])
		return (NULL);
	while (stored[i] && stored[i] != '\n')
		i++;
	if (stored[i] == '\n')
		i++;
	line = ft_substr(stored, 0, i);
	return (line);
}

static char	*trim_leftover(const char *stored)
{
	size_t	i;
	char	*new_stored;

	i = 0;
	if (!stored)
		return (NULL);
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i])
		return (NULL);
	i++;
	new_stored = ft_substr(stored, i, ft_strlen(stored) - i);
	if (!new_stored || !new_stored[0])
	{
		free(new_stored);
		return (NULL);
	}
	return (new_stored);
}

static char	*read_and_accumulate(int fd, char *stored)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*tmp;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		buffer[bytes_read] = '\0';
		if (!stored)
			stored = ft_substr(buffer, 0, bytes_read);
		else
		{
			tmp = ft_strjoin(stored, buffer);
			free(stored);
			stored = tmp;
		}
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stored);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*new_stored;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	g_stored = read_and_accumulate(fd, g_stored);
	if (!g_stored)
		return (NULL);
	line = extract_line(g_stored);
	new_stored = trim_leftover(g_stored);
	free(g_stored);
	g_stored = new_stored;
	return (line);
}
