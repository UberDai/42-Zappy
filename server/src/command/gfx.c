/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 19:06:29 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 20:03:47 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

void	gfx_client_connect(t_client *client, t_client *gfx_client)
{
	char	str[200];

	snprintf(str, 200, "* %u %s %u %u %u", client->id, client->team->name,
		client->position->x, client->position->y, client->orientation);
	if (gfx_client != NULL)
		network_send(gfx_client, str, 0);
	else
		network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_disconnect(t_client *client)
{
	char	str[20];

	snprintf(str, 20, "_ %u", client->id);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_promote(const t_client *client)
{
	char	str[6];

	snprintf(str, 6, "! %u", client->id);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_death(t_client *client)
{
	char	str[20];

	snprintf(str, 20, "x %u", client->id);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_victory(const t_team *team)
{
	char	str[23];

	snprintf(str, 23, "$ %s", team->name);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_tile_add(t_client *client, t_tile *tile, int item)
{
	char	str[20];

	snprintf(str, 20, "+ %u %u %i", tile->x, tile->y, item);
	if (client == NULL)
		network_send(NULL, str, NET_SEND_GFX);
	else
		network_send(client, str, 0);
}

void	gfx_egg_add(const t_egg *egg)
{
	char	str[100];

	snprintf(str, 10, "0 %s %u %u", egg->team->name, egg->position->x,
		egg->position->y);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_egg_remove(const t_egg *egg)
{
	char	str[100];

	snprintf(str, 10, "9 %s %u %u", egg->team->name, egg->position->x,
		egg->position->y);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_pick(t_client *client, int item)
{
	char	str[20];

	snprintf(str, 20, "^ %u %i", client->id, item);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_drop(t_client *client, int item)
{
	char	str[20];

	snprintf(str, 20, "v %u %i", client->id, item);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_move_to(t_client *client, t_tile *tile)
{
	char	str[20];

	snprintf(str, 20, "> %u %i %i", client->id, tile->x, tile->y);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_turn(t_client *client)
{
	char	str[20];

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

void	gfx_broadcast(const t_client *client)
{
	char	str[20];

	snprintf(str, 20, "b %u %i %i\n", client->id, client->position->x,
		client->position->y);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_send_map(t_client *client)
{
	t_uint	c[4];

	c[1] = 0;
	while (c[1] < g_zappy.height)
	{
		c[0] = 0;
		while (c[0] < g_zappy.width)
		{
			c[2] = 0;
			while (c[2] < ITEM_COUNT)
			{
				c[3] = 0;
				while (c[3] < g_zappy.map[c[1]][c[0]]->items[c[2]])
				{
					gfx_tile_add(client, g_zappy.map[c[1]][c[0]], c[2]);
					c[3]++;
				}
				c[2]++;
			}
			c[0]++;
		}
		c[1]++;
	}
}
