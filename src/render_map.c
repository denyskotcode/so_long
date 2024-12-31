/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:30:13 by dkot              #+#    #+#             */
/*   Updated: 2024/12/31 02:37:04 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"



// Free all textures
void cleanup_textures(void *mlx, t_textures *textures)
{
	mlx_destroy_image(mlx, textures->wall_img);
	mlx_destroy_image(mlx, textures->floor_img);
	mlx_destroy_image(mlx, textures->player_img);
	mlx_destroy_image(mlx, textures->collectible_img);
	mlx_destroy_image(mlx, textures->exit_img);
}

// Load textures from files
void declare_texture(t_textures *textures, void *mlx, int tile_size)
{
	textures->wall_img = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &tile_size, &tile_size);
	textures->floor_img = mlx_xpm_file_to_image(mlx, "textures/floor.xpm", &tile_size, &tile_size);
	textures->player_img = mlx_xpm_file_to_image(mlx, "textures/player.xpm", &tile_size, &tile_size);
	textures->collectible_img = mlx_xpm_file_to_image(mlx, "textures/collectible.xpm", &tile_size, &tile_size);
	textures->exit_img = mlx_xpm_file_to_image(mlx, "textures/exit.xpm", &tile_size, &tile_size);

	if (!textures->wall_img || !textures->floor_img || !textures->player_img ||
		!textures->collectible_img || !textures->exit_img)
		error_exit("Failed to load textures", NULL, NULL, -1);
}

void render_grid(void *mlx, void *win, t_map *map, int tile_size, t_textures *textures)
{
	int x, y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			mlx_put_image_to_window(mlx, win, textures->floor_img, x * tile_size, y * tile_size);
			if (map->grid[y][x] == '1')
				mlx_put_image_to_window(mlx, win, textures->wall_img, x * tile_size, y * tile_size);
			else if (map->grid[y][x] == 'P')
				mlx_put_image_to_window(mlx, win, textures->player_img, x * tile_size, y * tile_size);
			else if (map->grid[y][x] == 'C')
				mlx_put_image_to_window(mlx, win, textures->collectible_img, x * tile_size, y * tile_size);
			else if (map->grid[y][x] == 'E')
				mlx_put_image_to_window(mlx, win, textures->exit_img, x * tile_size, y * tile_size);
			x++;
		}
		y++;
	}
}

// Render the entire map
void render_map(t_map *map)
{
	void *mlx;
	void *win;
	int tile_size;
	int window_width;
	int window_height;
	t_textures textures;
	t_player player;

	tile_size = 50;
	window_width = map->width * tile_size;
	window_height = map->height * tile_size;
	mlx = mlx_init();
	if (!mlx)
		error_exit("Failed to initialize MiniLibX", NULL, NULL, -1);

	win = mlx_new_window(mlx, window_width, window_height, "so_long");
	if (!win)
	{
		mlx_destroy_display(mlx);
		free(mlx);
		error_exit("Failed to create window", NULL, NULL, -1);
	}
	declare_texture(&textures, mlx, tile_size);
	declare_player(&player);
	render_grid(mlx, win, map, tile_size, &textures);
	handle_events(mlx, win, map);
	mlx_loop(mlx);
	cleanup_textures(mlx, &textures);
	free_map(map);
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	free(mlx);
}

// Close the window and free resources
int close_window(t_map *map)
{
	free_map(map);
	exit(0);
}

// Handle keypress events
int handle_keypress(int keycode, t_map *map)
{
	if (keycode == 65307) // Escape key
		close_window(map);
	if (keycode == 119) //W
	{
		
	}
	if (keycode == 97)//A
	{
	
	}

	if (keycode == 115)//S
	{

	}

	if (keycode == 100)//D
	{

	}
	return (0);
}

// Set up event hooks
void handle_events(void *mlx, void *win, t_map *map)
{
	mlx_hook(win, 2, 1L << 0, handle_keypress, map); // Key press
	mlx_hook(win, 17, 0, close_window, map);		 // Window close
}

void declare_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->moves = 0;
}