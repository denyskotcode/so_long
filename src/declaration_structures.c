/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declaration_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 23:29:25 by dkot              #+#    #+#             */
/*   Updated: 2024/12/28 23:30:03 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void declare_map(t_map *map)
{
	map->width = 0;
	map->height = 0;
	map->player_count = 0;
	map->exit_count = 0;
	map->collectible_count = 0;
}
void declare_line(t_line *line)
{
	line->last_line = NULL;
	line->line = NULL;
	line->line_length = 0;
}
