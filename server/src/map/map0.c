/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map0.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/14 23:42:00 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/15 00:25:04 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>
#include <strings.h>

static void	*map_create_tile(t_uint x, t_uint y)
{
	t_tile	*tile;

	tile = malloc(sizeof(t_tile));
	tile->position.x = x;
	tile->position.y = y;
	bzero(&(tile->inventory), sizeof(t_inventory));
	return (tile);
}

void		map_init(void)
{
	t_uint	x;
	t_uint	y;

	y = 0;
	while (y < g_zappy.height)
	{
		x = 0;
		while (x < g_zappy.width)
		{
			g_zappy.map[y][x] = map_create_tile(x, y);
			x++;
		}
		y++;
	}
}