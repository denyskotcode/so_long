/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 02:20:04 by dkot              #+#    #+#             */
/*   Updated: 2024/12/31 05:54:06 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	allocation_map(const char *filename, t_map *map)
{
	int		i;
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Unable to open file", NULL, NULL, -1);
	map->grid = malloc(sizeof(char *) * map->height);
	if (!map->grid)
		error_exit("Allocation fail", NULL, NULL, -1);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map->grid[i] = ft_strdup(line);
		if (!map->grid[i])
			error_exit("Allocation fail", line, NULL, fd);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i])
		{
			free(map->grid[i]);
			map->grid[i] = NULL;
		}
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}
