/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 06:03:56 by dkot              #+#    #+#             */
/*   Updated: 2024/12/31 06:18:41 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cleanup_textures(void *mlx, t_t *textures)
{
	mlx_destroy_image(mlx, textures->w);
	mlx_destroy_image(mlx, textures->f);
	mlx_destroy_image(mlx, textures->p);
	mlx_destroy_image(mlx, textures->c);
	mlx_destroy_image(mlx, textures->e);
}

void	declare_texture(t_t *t, void *mlx, int tile_size)
{
	t->w = mlx_xpm_file_to_image
		(mlx, "textures/wall.xpm", &tile_size, &tile_size);
	t->f = mlx_xpm_file_to_image
		(mlx, "textures/bg.xpm", &tile_size, &tile_size);
	t->p = mlx_xpm_file_to_image
		(mlx, "textures/player.xpm", &tile_size, &tile_size);
	t->c = mlx_xpm_file_to_image
		(mlx, "textures/item.xpm", &tile_size, &tile_size);
	t->e = mlx_xpm_file_to_image
		(mlx, "textures/exit.xpm", &tile_size, &tile_size);
	if (!t->w || !t->f || !t->p
		|| !t->c || !t->e)
		error_exit("Failed to load textures", NULL, NULL, -1);
}
