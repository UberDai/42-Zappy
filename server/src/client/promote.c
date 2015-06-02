/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 22:01:38 by amaurer           #+#    #+#             */
/*   Updated: 2015/06/03 00:19:49 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

t_uint		g_promotion_needs[MAX_LEVEL][ITEM_COUNT] = {
	{ 1, 1, 0, 0, 0, 0, 0 },
	{ 2, 1, 1, 1, 0, 0, 0 },
	{ 2, 2, 0, 1, 0, 2, 0 },
	{ 4, 1, 1, 2, 0, 1, 0 },
	{ 4, 1, 2, 1, 3, 0, 0 },
	{ 6, 1, 2, 3, 0, 1, 0 },
	{ 6, 2, 2, 2, 2, 2, 1 }
};

static short	client_can_promote(t_client *client)
{
	t_uint		i;
	t_client	**clients;
	t_tile		*tile;

	tile = client->position;

	if (tile->client_count < g_promotion_needs[client->level][0])
		return (0);
	clients = tile->clients;
	i = 0;
	while (i < tile->client_count)
	{
		if (clients[i]->level != client->level)
			return (0);
		i++;
	}
	i = 1;
	while (i < ITEM_COUNT)
	{
		if (g_promotion_needs[client->level][i] > tile->items[i])
			return (0);
		i++;
	}
	return (1);
}

short		client_promote(t_client *client)
{
	t_tile	*tile;
	t_uint	i;

	tile = client->position;
	tile_update_client_list(tile);
	if (client->level >= MAX_LEVEL - 1 || !client_can_promote(client))
		return (0);

	i = 1;
	while (i < ITEM_COUNT)
	{
		tile->items[i] -= g_promotion_needs[client->level][i];
		i++;
	}
	i = 0;
	while (i < tile->client_count)
	{
		tile->clients[i]->level++;
		i++;
	}
	return (1);
}