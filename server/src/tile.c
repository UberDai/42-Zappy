/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/10 21:06:57 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 21:12:29 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <limits.h>
#include <string.h>
#include <stdlib.h>

void		*tile_create(t_uint x, t_uint y)
{
	t_tile	*tile;

	tile = calloc(1, sizeof(t_tile));
	bzero(tile, sizeof(tile));
	tile->x = x;
	tile->y = y;
	return (tile);
}

t_tile		*tile_at(int x, int y)
{
	t_tile	*tile;

	while (x < 0)
		x += g_zappy.width;
	while (y < 0)
		y += g_zappy.height;
	x %= (int)g_zappy.width;
	y %= (int)g_zappy.height;
	tile = g_zappy.map[y][x];
	return (tile);
}

short		tile_add_item(t_tile *tile, int item)
{
	if (item < 0 || item >= ITEM_COUNT)
		return (0);
	if (tile->items[item] == UINT_MAX)
		return (0);
	tile->items[item]++;
	return (1);
}

short		tile_remove_item(t_tile *tile, int item)
{
	if (item < 0 || item >= ITEM_COUNT)
		return (0);
	if (tile->items[item] == 0)
		return (0);
	tile->items[item]--;
	return (1);
}
