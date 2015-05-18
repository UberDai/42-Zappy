/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/16 22:44:34 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/18 03:29:08 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdio.h>
#include <libft.h>
#include <stdlib.h>
#include <string.h>

t_client	*client_create(t_tile *position)
{
	static t_uint	id;
	t_client		*client;
	t_client		*clients;

	if (id == 0)
		id = 1;
	client = malloc(sizeof(t_client));
	bzero(client, sizeof(t_client));
	client->hunger = FOOD_DURATION;
	client_move(client, position);
	client->id = id++;
	clients = g_zappy.clients;
	if (clients == NULL)
		g_zappy.clients = client;
	else
	{
		while (clients->next)
			clients = clients->next;
		clients->next = client;
	}
	return (client);
}

void	client_delete(t_client *client_to_delete)
{
	t_client	*client;

	client = g_zappy.clients;
	if (client == client_to_delete)
		g_zappy.clients = client->next;
	else
	{
		while (client && client->next == client_to_delete)
			client = client->next;

		if (client == NULL)
			return ;

		client->next = client_to_delete->next;
	}

	client_to_delete->position->client_count--;
	free(client_to_delete);
}

short	client_move(t_client *client, t_tile *tile)
{
	if (client->position != NULL)
	{
		client->position->client_count--;
		client->position->refresh_client_list = 1;
	}
	tile->client_count++;
	tile->refresh_client_list = 1;
	client->position = tile;
	return (1);
}

short	client_eat(t_client *client)
{
	if (client->items[ITEM_FOOD] == 0)
		return (0);
	client->items[ITEM_FOOD]--;
	client->hunger = FOOD_DURATION;
	return (1);
}

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