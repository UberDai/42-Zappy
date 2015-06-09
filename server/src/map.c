/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/14 23:42:00 by amaurer           #+#    #+#             */
/*   Updated: 2015/06/10 00:18:26 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>
#include <strings.h>
#include <limits.h>

static void	*tile_create(t_uint x, t_uint y)
{
	t_tile	*tile;

	tile = calloc(1, sizeof(t_tile));
	bzero(tile, sizeof(tile));
	tile->x = x;
	tile->y = y;
	tile->refresh_client_list = 1;
	return (tile);
}

void		map_init(void)
{
	t_uint	x;
	t_uint	y;

	g_zappy.map = calloc(g_zappy.height, sizeof(t_tile **));
	y = 0;
	while (y < g_zappy.height)
	{
		g_zappy.map[y] = calloc(g_zappy.width, sizeof(t_tile *));
		x = 0;
		while (x < g_zappy.width)
		{
			g_zappy.map[y][x] = tile_create(x, y);
			x++;
		}
		y++;
	}
}

void	tile_update_client_list(t_tile *tile)
{
	t_client	*client;
	t_lstiter	iter;
	t_uint		i;

	if (!tile->refresh_client_list)
		return ;
	tile->refresh_client_list = 0;

	if (tile->clients != NULL)
		free(tile->clients);

	if (tile->client_count == 0)
		tile->clients = NULL;
	else
	{
		tile->clients = calloc(tile->client_count, sizeof(t_client *));
		init_iter(&iter, g_zappy.clients, increasing);
		i = 0;
		while (lst_iterator_next(&iter))
		{
			client = iter.data;
			if (client->position == tile)
			{
				tile->clients[i] = client;
				i++;
			}
		}
	}
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
	if (tile->refresh_client_list)
		tile_update_client_list(tile);
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

void		map_regenerate(void)
{
	t_uint	x;
	t_uint	y;

	y = 0;
	while (y < g_zappy.height)
	{
		x = 0;
		while (x < g_zappy.width)
		{
			tile_regenerate(g_zappy.map[y][x]);
			x++;
		}
		y++;
	}
}

void		tile_regenerate(t_tile *tile)
{
	t_uint	i;
	t_uint	j;
	t_uint	amount;

	i = 0;
	while (i < ITEM_COUNT)
	{
		amount = rand_range(0, REGEN_MAX);
		tile->items[i] += amount;
		j = 0;
		while (j < amount)
		{
			gfx_tile_add(NULL, tile, i);
			j++;
		}
		i++;
	}
}

char	*tile_inventory(t_tile *tile)
{
	char	*str;

	str = calloc(200, sizeof(char));
	snprintf(str, 200, "food %u linemate %u deraumere %u sibur %u "
		"mendiane %u phiras %u thystame %u",
		tile->items[0],
		tile->items[1],
		tile->items[2],
		tile->items[3],
		tile->items[4],
		tile->items[5],
		tile->items[6]
	);
	return (str);
}
