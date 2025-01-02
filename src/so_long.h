/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:40:14 by dkot              #+#    #+#             */
/*   Updated: 2025/01/02 05:53:56 by dkot             ###   ########.fr       */
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
}			t_map;

typedef struct s_line
{
	char	*line;
	char	*last_line;
	int		line_length;
}			t_line;

typedef struct s_player
{
	int		x;
	int		y;
	int		moves;
}			t_player;

typedef struct s_textures
{
	void	*w;
	void	*f;
	void	*p;
	void	*c;
	void	*e;
}			t_t;

typedef struct s_new_coord
{
	int	new_x;
	int	new_y;
}	t_new_coord;

typedef struct s_render
{
	int			tile_size;
	void		*mlx;
	void		*win;
	t_t			t;
}				t_render;

typedef struct s_game
{
	t_map		*map;
	t_player	*player;
	t_render	*render;
}				t_game;

void		cleanup_textures(void *mlx, t_t *t);
void		declare_texture(t_t *t, void *mlx, int tile_size);
void		render_grid(t_render *render, t_map *map, t_player *player);
void		declare_player(t_map *map, t_player *player);
int			handle_keypress(int keycode, t_game *game);
void		processing_moves(t_map *map, t_player *player, t_new_coord c,
				t_render *render);
int			close_window(t_map *map);
void		handle_events(t_game *game);
void		render_map(t_map *map);
void		declare_map(t_map *map);
void		declare_line(t_line *line);
void		error_exit(char *message, char *line, char *last_line, int fd);
void		check_t_map(t_map *map);
void		process_line(t_line *lines, t_map *map, int fd);
void		parse_map(const char *filename, t_map *map);
void		check_middle_line(t_line *lines, t_map *map, int fd);
void		check_first_and_last_line(int line_length, int fd, char *line);
void		check_map_width(t_line *lines, t_map *map, int fd);
void		allocation_map(const char *filename, t_map *map);
void		free_map(t_map *map);
char		*get_next_line(int fd);
static void	init_game(t_map *map,
				t_game *game, t_render *render, t_player *player);

#endif
