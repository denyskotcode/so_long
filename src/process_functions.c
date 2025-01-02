/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 05:35:03 by dkot              #+#    #+#             */
/*   Updated: 2025/01/02 05:36:43 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	processing_moves(t_map *map, t_player *player,
			t_new_coord c, t_render *render)
{
	if (map->grid[c.new_y][c.new_x] == 'E' && map->collectible_count == 0)
	{
		ft_printf("Moves: %d\n", player->moves);
		close_window(map);
	}
	else if (map->grid[c.new_y][c.new_x] == 'C')
	{
		map->collectible_count--;
		map->grid[player->y][player->x] = '0';
		map->grid[c.new_y][c.new_x] = 'P';
		player->x = c.new_x;
		player->y = c.new_y;
		ft_printf("Moves: %d\n", player->moves++);
	}
	else if (map->grid[c.new_y][c.new_x] == '0')
	{
		map->grid[player->y][player->x] = '0';
		map->grid[c.new_y][c.new_x] = 'P';
		player->x = c.new_x;
		player->y = c.new_y;
		ft_printf("Moves: %d\n", player->moves++);
	}
	render_grid(render, map, player);
}

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
	t_new_coord	c;

	c.new_x = game->player->x;
	c.new_y = game->player->y;
	if (keycode == 65307)
		close_window(game->map);
	if (keycode == 119 || keycode == 65362)
		c.new_y--;
	else if (keycode == 97 || keycode == 65361)
		c.new_x--;
	else if (keycode == 115 || keycode == 65364)
		c.new_y++;
	else if (keycode == 100 || keycode == 65363)
		c.new_x++;
	if (game->map->grid[c.new_y][c.new_x] != '1')
		processing_moves(
			game->map, game->player, c, game->render);
	return (0);
}

int	close_window(t_map *map)
{
	free_map(map);
	exit(0);
}

void	handle_events(t_game *game)
{
	mlx_hook(game->render->win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->render->win, 17, 0, close_window, game->map);
}
