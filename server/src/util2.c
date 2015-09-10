/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/10 19:42:49 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 19:44:10 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdio.h>

void	print_client(t_client *client)
{
	if (client->status == STATUS_GFX)
		printf("#%u gfx\n", client->id);
	else
	{
		printf("#%u [%i;%i", client->id, client->position->x,
			client->position->y);
		if (client->orientation == ORIENT_NORTH)
			printf(";N]");
		else if (client->orientation == ORIENT_SOUTH)
			printf(";S]");
		else if (client->orientation == ORIENT_EAST)
			printf(";E]");
		else if (client->orientation == ORIENT_WEST)
			printf(";W]");
		else
			printf("]");
		printf(
			" Hunger: %u   F: %u, L: %u, D: %u, S: %u, M: %u, P: %u, T: %u\n",
			client->hunger, client->items[0],
			client->items[1], client->items[2],
			client->items[3], client->items[4],
			client->items[5], client->items[6]);
	}
}

void	print_client_queue(t_client *client)
{
	t_uint	i;

	printf("Queue #%u:\n", client->id);
	i = 0;
	while (i < CLIENT_QUEUE_MAX && client->queue[i].set)
	{
		printf("  [%u] %s (%u)\n", i, client->queue[i].av[0],
			client->queue[i].delay);
		i++;
	}
	printf("\n");
}

void	print_client_positions(void)
{
	t_uint	x;
	int		y;

	y = g_zappy.height;
	while (y >= 0)
	{
		x = 0;
		while (x < g_zappy.width)
		{
			printf(" %lu ", tile_at(x, y)->clients.size);
			x++;
		}
		printf("\n");
		y--;
	}
}

void	print_tile(t_tile *tile)
{
	printf("Tile [%i;%i]   F: %u, L: %u, D: %u, S: %u, M: %u, P: %u, T: %u\n",
		tile->x, tile->y, tile->items[0],
		tile->items[1], tile->items[2],
		tile->items[3], tile->items[4],
		tile->items[5], tile->items[6]);
}
