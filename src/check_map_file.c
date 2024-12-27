/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:40:04 by dkot              #+#    #+#             */
/*   Updated: 2024/12/27 04:40:59 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void error_exit(char *message)
{
    ft_printf("Error: %s\n");
    exit(EXIT_FAILURE);
}

void declare_map(t_map*map)
{
	map->width = 0;
	map->height = 0;
	map->player_count = 0;
	map->exit_count = 0;
	map->collectible_count = 0;
}
void parse_map(const char *filename, t_map*map)
{
	char *line;
	int line_length;

	declare_map(map);
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Unable to open file");
	while ((line = get_next_line(fd)) != NULL)
	{
        line_length = ft_strlen(line);
		check_map_width(line_length, map, fd, line);
		error_check(line, line_length, map);
		map->height++;
		free(line);
	}

	
}

void check_map_width (int line_length, t_map*map, int fd, char * line)
{
        if (map->width == 0)
            map->width = line_length;
        else if (line_length != map->width)
		{
            free(line);
            close(fd);
            error_exit("Map is not rectangular");
        }
}

int	error_check(char * line, int line_length, t_map*map)
{
	int i;
	static int	first_line;

	i = 0;
	while (i < line_length)
	{
		if (first_line == 0)
		{
			if (line[i] != '1')
				error_exit("Border error");
			else
			{
				if (line[i] == 'P') (map->player_count)++;
				else if (line[i] == 'E') (map->exit_count)++;
				else if (line[i] == 'C') (map->collectible_count)++;
				else if (line[i] != '0' && line[i] != '1' && line[i] != '\n') {
                free(line);
                close(fd);
                fprintf(stderr, "Error: Invalid character in map\n");
                exit(EXIT_FAILURE);
            }
			}
		i++;
		}
	}
	if (first_line == 0)
		first_line++;
}

