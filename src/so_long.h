/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:40:14 by dkot              #+#    #+#             */
/*   Updated: 2024/12/27 01:58:58 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define MINITALK_H

# include "../libs/libft/libft.h"
# include "../libs/libftprintf/ft_printf.h"
# include "../libs/get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>

typedef struct s_map {
    char **grid;      // 2D array of characters representing the map
    int width;        // Number of columns in the map
    int height;       // Number of rows in the map
    int player_count; // Number of players ('P') in the map
    int exit_count;   // Number of exits ('E') in the map
    int collectible_count; // Number of collectibles ('C') in the map
} t_map;


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

void	error_exit(char *message);

#endif
