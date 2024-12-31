/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 06:09:02 by dkot              #+#    #+#             */
/*   Updated: 2024/12/31 06:22:39 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_grid(t_render *r, t_map *map, t_player *player)
{
	int	x;
	int	y;
	int	s;

	s = r->tile_size;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			mlx_put_image_to_window(r->mlx, r->win, r->t.f, x * s, y * s);
			if (map->grid[y][x] == '1')
				mlx_put_image_to_window(r->mlx, r->win, r->t.w, x * s, y * s);
			else if (map->grid[y][x] == 'C')
				mlx_put_image_to_window(r->mlx, r->win, r->t.c, x * s, y * s);
			else if (map->grid[y][x] == 'E')
				mlx_put_image_to_window(r->mlx, r->win, r->t.e, x * s, y * s);
			else if (x == player->x && y == player->y)
				mlx_put_image_to_window(r->mlx, r->win, r->t.p, x * s, y * s);
			x++;
		}
		y++;
	}
}
int	handle_keypress(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player->x;
	new_y = game->player->y;
	if (keycode == 65307)
		close_window(game->map);
	if (keycode == 119 || keycode == 65362)
		new_y--;
	else if (keycode == 97 || keycode == 65361)
		new_x--;
	else if (keycode == 115  || keycode == 65364)
		new_y++;
	else if (keycode == 100 || keycode == 65363)
		new_x++;
	if (game->map->grid[new_y][new_x] != '1')
		processing_moves(
			game->map, game->player, new_x, new_y, game->render);
	return (0);
}

void	processing_moves(t_map *map, t_player *player, int new_x, int new_y, t_render *render)
{
	if (map->grid[new_y][new_x] == 'E' && map->collectible_count == 0)
	{
		player->moves++;
		ft_printf("Moves: %d\n", player->moves);
		close_window(map);
	}
	else if (map->grid[new_y][new_x] == 'C') // Collectible
	{
		map->grid[new_y][new_x] = '0'; // Remove collectible
		map->collectible_count--;
		map->grid[player->y][player->x] = '0'; // Clear old position
		map->grid[new_y][new_x] = 'P';		   // Set new position
		player->x = new_x;
		player->y = new_y;
		player->moves++;
		ft_printf("Moves: %d\n", player->moves);
	}
	else if (map->grid[new_y][new_x] == '0') // Empty space
	{
		map->grid[player->y][player->x] = '0'; // Clear old position
		map->grid[new_y][new_x] = 'P';		   // Set new position
		player->x = new_x;
		player->y = new_y;
		player->moves++;
		ft_printf("Moves: %d\n", player->moves);
	}

	render_grid(render, map, player); // Re-render the grid
}

// Close the window and exit the program
int close_window(t_map *map)
{
	free_map(map);
	exit(0);
}
void	handle_events(t_game *game)
{
	mlx_hook(game->render->win, 2, 1L << 0, handle_keypress, game); // Key press
	mlx_hook(game->render->win, 17, 0, close_window, game->map);	// Window close
}

// Render the entire map
void render_map(t_map *map)
{
	t_game game;
	t_render render;
	t_player player;

	game.map = map;
	game.player = &player;
	game.render = &render;

	render.tile_size = 50;
	int window_width = map->width * render.tile_size;
	int window_height = map->height * render.tile_size;

	render.mlx = mlx_init();
	if (!render.mlx)
		error_exit("Failed to initialize MiniLibX", NULL, NULL, -1);

	render.win = mlx_new_window(render.mlx, window_width, window_height, "so_long");
	if (!render.win)
	{
		mlx_destroy_display(render.mlx);
		free(render.mlx);
		error_exit("Failed to create window", NULL, NULL, -1);
	}

	declare_texture(&render.t, render.mlx, render.tile_size);
	declare_player(map, game.player);
	render_grid(&render, map, game.player);
	handle_events(&game);
	mlx_loop(render.mlx);

	cleanup_textures(render.mlx, &render.t);
	free_map(map);
	mlx_destroy_window(render.mlx, render.win);
	mlx_destroy_display(render.mlx);
	free(render.mlx);
}
