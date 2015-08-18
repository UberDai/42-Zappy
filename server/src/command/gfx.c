/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 19:06:29 by amaurer           #+#    #+#             */
/*   Updated: 2015/08/18 23:58:25 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

void	gfx_client_connect(t_client *client, t_client *gfx_client)
{
	char	str[200] = { 0 };

	snprintf(str, 200, "* %u %s %u %u %u", client->id, client->team->name,
		client->position->x, client->position->y, client->orientation);
	if (gfx_client != NULL)
		network_send(gfx_client, str, 0);
	else
		network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_disconnect(t_client *client)
{
	char	str[20] = { 0 };

	snprintf(str, 20, "_ %u", client->id);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_promote(const t_client *client)
{
	char	str[6] = { 0 };

	snprintf(str, 6, "! %u", client->id);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_death(t_client *client)
{
	char	str[20] = { 0 };

	snprintf(str, 20, "x %u", client->id);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_tile_add(t_client *client, t_tile *tile, int item)
{
	char	str[20] = { 0 };

	snprintf(str, 20, "+ %u %u %i", tile->x, tile->y, item);
	if (client == NULL)
		network_send(NULL, str, NET_SEND_GFX);
	else
		network_send(client, str, 0);
}

void	gfx_egg_add(const t_egg *egg)
{
	char	str[10] = { 0 };

	snprintf(str, 10, "0 %u %u", egg->position->x, egg->position->y);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_egg_remove(const t_egg *egg)
{
	char	str[10] = { 0 };

	snprintf(str, 10, "9 %u %u", egg->position->x, egg->position->y);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_pick(t_client *client, int item)
{
	char	str[20] = { 0 };;

	snprintf(str, 20, "^ %u %i", client->id, item);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_drop(t_client *client, int item)
{
	char	str[20] = { 0 };;

	snprintf(str, 20, "v %u %i", client->id, item);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_move_to(t_client *client, t_tile *tile)
{
	char	str[20] = { 0 };;

	snprintf(str, 20, "> %u %i %i", client->id, tile->x, tile->y);
	network_send(NULL, str, NET_SEND_GFX);
}


void	gfx_client_turn(t_client *client)
{
	char	str[20] = { 0 };;

	snprintf(str, 20, "o %u %i", client->id, client->orientation);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_send_clients(t_client *client)
{
	t_lstiter	iter;

	init_iter(&iter, g_zappy.clients, increasing);
	while (lst_iterator_next(&iter))
		gfx_client_connect(iter.data, client);
}

void	gfx_send_map(t_client *client)
{
	t_uint	x;
	t_uint	y;
	t_uint	i;
	t_uint	j;

	y = 0;
	while (y < g_zappy.height)
	{
		x = 0;
		while (x < g_zappy.width)
		{
			i = 0;
			while (i < ITEM_COUNT)
			{
				j = 0;
				while (j < g_zappy.map[y][x]->items[i])
				{
					gfx_tile_add(client, g_zappy.map[y][x], i);
					j++;
				}
				i++;
			}
			x++;
		}
		y++;
	}
}
