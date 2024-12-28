/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 21:55:10 by dkot              #+#    #+#             */
/*   Updated: 2024/12/28 23:33:22 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void error_exit(char *message, char *line, char *last_line, int fd)
{
	if (line)
		free(line);
	if (last_line)
		free(last_line);
	if (fd >= 0)
		close(fd);

	ft_printf("Error: %s\n", message);
	exit(EXIT_FAILURE);
}





void check_middle_line(t_line *lines, t_map *map, int fd)
{
	int i = 1;

	if (lines->line[0] != '1' || lines->line[lines->line_length - 1] != '1')
		error_exit("Borders are incorrect", lines->line, lines->last_line, fd);

	while (i < lines->line_length - 1)
	{
		if (!ft_strchr("01CEP", lines->line[i]))
			error_exit("Invalid symbol in map", lines->line, lines->last_line, fd);

		if (lines->line[i] == 'C')
			map->collectible_count++;
		else if (lines->line[i] == 'E')
			map->exit_count++;
		else if (lines->line[i] == 'P')
			map->player_count++;

		i++;
	}
}

void check_first_and_last_line(int line_length, int fd, char *line)
{
	int i = 0;

	while (i < line_length)
	{
		if (line[i] != '1')
			error_exit("Borders are incorrect", line, NULL, fd);
		i++;
	}
}

void check_map_width(t_line *lines, t_map *map, int fd)
{
	if (map->width == 0)
		map->width = lines->line_length;
	else if (lines->line_length != map->width)
		error_exit("Map is not rectangular", lines->line, lines->last_line, fd);
}

void check_t_map(t_map *map)
{
	if (map->player_count != 1)
		error_exit("Player count error", NULL, NULL, -1);
	if (map->collectible_count < 1)
		error_exit("No collectibles in map", NULL, NULL, -1);
	if (map->exit_count != 1)
		error_exit("Exit count error", NULL, NULL, -1);
}

void parse_map(const char *filename, t_map *map)
{
	t_line lines;
	int fd;

	declare_line(&lines);
	declare_map(map);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Unable to open file", NULL, NULL, -1);
	while ((lines.line = get_next_line(fd)) != NULL)
	{
		lines.line_length = ft_strlen(lines.line);
		if (lines.line[lines.line_length - 1] == '\n')
			lines.line[lines.line_length - 1] = '\0';
		lines.line_length = ft_strlen(lines.line);
		if (map->height == 0)
			check_first_and_last_line(lines.line_length, fd, lines.line);
		else
			check_middle_line(&lines, map, fd);
		check_map_width(&lines, map, fd);
		if (lines.last_line)
			free(lines.last_line);
		lines.last_line = ft_strdup(lines.line);
		map->height++;
		free(lines.line);
	}
	if (!lines.last_line)
		error_exit("Empty map file", NULL, NULL, fd);
	check_first_and_last_line(lines.line_length, fd, lines.last_line);
	free(lines.last_line);
	close(fd);
	check_t_map(map);
}
