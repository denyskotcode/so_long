/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 21:55:10 by dkot              #+#    #+#             */
/*   Updated: 2024/12/29 02:05:17 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(char *message, char *line, char *last_line, int fd)
{
	if (line)
		free(line);
	if (last_line)
		free(last_line);
	if (fd >= 0)
		close(fd);
    free_gnl_buffer();
	ft_printf("Error: %s\n", message);
	exit(EXIT_FAILURE);
}

void	check_t_map(t_map *map)
{
	if (map->player_count != 1)
		error_exit("Player count error", NULL, NULL, -1);
	if (map->collectible_count < 1)
		error_exit("No collectibles in map", NULL, NULL, -1);
	if (map->exit_count != 1)
		error_exit("Exit count error", NULL, NULL, -1);
}

void	process_line(t_line *lines, t_map *map, int fd)
{
	lines->line_length = ft_strlen(lines->line);
	if (lines->line[lines->line_length - 1] == '\n')
		lines->line[lines->line_length - 1] = '\0';
	lines->line_length = ft_strlen(lines->line);
	if (map->height == 0)
		check_first_and_last_line(lines->line_length, fd, lines->line);
	else
		check_middle_line(lines, map, fd);
	check_map_width(lines, map, fd);
	if (lines->last_line)
		free(lines->last_line);
	lines->last_line = ft_strdup(lines->line);
	map->height++;
	free(lines->line);
}

void	parse_map(const char *filename, t_map *map)
{
	t_line	lines;
	int		fd;

	declare_line(&lines);
	declare_map(map);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Unable to open file", NULL, NULL, -1);
	lines.line = get_next_line(fd);
	while (lines.line != NULL)
	{
		process_line(&lines, map, fd);
		lines.line = get_next_line(fd);
	}
	if (!lines.last_line)
		error_exit("Empty map file", NULL, NULL, fd);
	check_first_and_last_line(ft_strlen(lines.last_line), fd, lines.last_line);
	free(lines.last_line);
	close(fd);
	check_t_map(map);
}
