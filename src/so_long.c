/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkot <dkot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:40:11 by dkot              #+#    #+#             */
/*   Updated: 2024/12/31 02:14:39 by dkot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_map	map;

	if (argc != 2)
		error_exit("argument error", NULL, NULL, -1);
	parse_map(argv[1], &map);
	allocation_map(argv[1], &map);
	render_map(&map);

}
