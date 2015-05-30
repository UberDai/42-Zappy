/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/14 23:42:00 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/30 21:17:06 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>
#include <strings.h>

static void	*tile_create(t_uint x, t_uint y)
{
	t_tile	*tile;

	tile = malloc(sizeof(t_tile));
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

	g_zappy.map = malloc(sizeof(t_tile **) * g_zappy.height);
	y = 0;
	while (y < g_zappy.height)
	{
		g_zappy.map[y] = malloc(sizeof(t_tile *) * g_zappy.width);
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
		tile->clients = malloc(sizeof(t_client *) * tile->client_count);
		client = g_zappy.clients;
		i = 0;
		while (client)
		{
			if (client->position == tile)
			{
				tile->clients[i] = client;
				i++;
			}
			DLIST_FORWARD(t_client*, client);
		}
	}
}

t_tile		*tile_at(int x, int y)
{
	t_tile	*tile;
	printf("%i %i\n", x, y);

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
