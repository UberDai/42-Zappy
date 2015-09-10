/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 19:06:29 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 21:04:18 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

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
