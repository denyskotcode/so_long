/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 23:35:46 by dkot              #+#    #+#             */
/*   Updated: 2024/12/29 01:42:23 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_middle_line(t_line *lines, t_map *map, int fd)
{
	int	i;

	i = 1;
	if (lines->line[0] != '1' || lines->line[lines->line_length - 1] != '1')
		error_exit("Borders are incorrect", lines->line, lines->last_line, fd);
	while (i < lines->line_length - 1)
	{
		if (!ft_strchr("01CEP", lines->line[i]))
			error_exit("Invalid symbol in map",
				lines->line, lines->last_line, fd);
		if (lines->line[i] == 'C')
			map->collectible_count++;
		else if (lines->line[i] == 'E')
			map->exit_count++;
		else if (lines->line[i] == 'P')
			map->player_count++;
		i++;
	}
}

void	check_first_and_last_line(int line_length, int fd, char *line)
{
	int	i;

	i = 0;
	while (i < line_length)
	{
		if (line[i] != '1')
			error_exit("Borders are incorrect", line, NULL, fd);
		i++;
	}
}

void	check_map_width(t_line *lines, t_map *map, int fd)
{
	if (map->width == 0)
		map->width = lines->line_length;
	else if (lines->line_length != map->width)
		error_exit("Map is not rectangular", lines->line, lines->last_line, fd);
}
