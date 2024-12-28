/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:40:14 by dkot              #+#    #+#             */
/*   Updated: 2024/12/28 23:28:48 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define MINITALK_H

# include "../libs/libft/libft.h"
# include "../libs/libftprintf/ft_printf.h"
//# include "../libs/get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>

typedef struct s_map {
    char **grid;
    int width;
    int height;
    int player_count;
    int exit_count;
    int collectible_count;
} t_map;

typedef struct s_line {
	char *line;
	char *last_line;
	int line_length;
} t_line;

typedef struct	s_player
{
	int x;
	int y;
	int moves;
} t_player;

typedef struct	s_game
{
	t_map map;
	t_player player;
	void *mlx;
	void *window;
} t_game;

void error_exit(char *message, char *line, char *last_line, int fd);
void declare_map(t_map *map);
void declare_line(t_line *line);
void parse_map(const char *filename, t_map *map);
void check_map_width(t_line *lines, t_map *map, int fd);
void check_first_and_last_line(int line_length, int fd, char *line);
void check_middle_line(t_line *lines, t_map *map, int fd);
void check_t_map(t_map *map);
char *get_next_line(int fd); //not for entaire time, but for some time

#endif
