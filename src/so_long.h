/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:40:14 by dkot              #+#    #+#             */
/*   Updated: 2024/12/31 02:10:56 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/libft/libft.h"
# include "../libs/libftprintf/ft_printf.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_count;
	int		exit_count;
	int		collectible_count;
}	t_map;

/* Line structure */
typedef struct s_line
{
	char	*line;
	char	*last_line;
	int		line_length;
}	t_line;

typedef struct s_player
{
	int	x;
	int	y;
	int	moves;
}	t_player;

typedef struct s_game
{
	t_map		map;
	t_player	player;
	void		*mlx;
	void		*window;
}	t_game;

typedef struct s_textures
{
	void *wall_img;
    void *floor_img;
    void *player_img;
    void *collectible_img;
    void *exit_img;
    int x;
	int y;
}	t_textures;
void	error_exit(char *message, char *line, char *last_line, int fd);
void	declare_map(t_map *map);
void	declare_line(t_line *lines);
void	check_t_map(t_map *map);
void	check_middle_line(t_line *lines, t_map *map, int fd);
void	check_first_and_last_line(int line_length, int fd, char *line);
void	check_map_width(t_line *lines, t_map *map, int fd);
void	process_line(t_line *lines, t_map *map, int fd);
void	parse_map(const char *filename, t_map *map);
void	free_gnl_buffer(void);
void	allocation_map(const char *filename, t_map *map);
char	*get_next_line(int fd); //temp variant
void	print_map(t_map *map);
void free_map(t_map *map);
void cleanup_textures(void *mlx, t_textures *textures);
void declare_texture(t_textures *textures, void *mlx, int tile_size);
void render_grid(void *mlx, void *win, t_map *map, int tile_size, t_textures *textures);
void render_map(t_map *map);
int close_window(t_map *map);
int handle_keypress(int keycode, t_map *map);
void handle_events(void *mlx, void *win, t_map *map);

#endif
