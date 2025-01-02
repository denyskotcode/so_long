/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 06:09:02 by dkot              #+#    #+#             */
/*   Updated: 2025/01/02 05:54:58 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_game(t_map *map, t_game *game
					, t_render *render, t_player *player)
{
	int	window_width;
	int	window_height;

	render->tile_size = 50;
	window_width = map->width * render->tile_size;
	window_height = map->height * render->tile_size;
	game->map = map;
	game->player = player;
	game->render = render;
	render->mlx = mlx_init();
	if (!render->mlx)
		error_exit("Failed to initialize MiniLibX", NULL, NULL, -1);
	render->win = mlx_new_window(render->mlx, window_width, window_height,
			"so_long");
	if (!render->win)
	{
		mlx_destroy_display(render->mlx);
		free(render->mlx);
		error_exit("Failed to create window", NULL, NULL, -1);
	}
	declare_texture(&render->t, render->mlx, render->tile_size);
	declare_player(map, game->player);
}

void	render_map(t_map *map)
{
	t_game		game;
	t_render	render;
	t_player	player;

	init_game(map, &game, &render, &player);
	render_grid(&render, map, &player);
	handle_events(&game);
	mlx_loop(render.mlx);
	cleanup_textures(render.mlx, &render.t);
	free_map(map);
	mlx_destroy_window(render.mlx, render.win);
	mlx_destroy_display(render.mlx);
	free(render.mlx);
}
