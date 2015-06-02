/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 19:06:29 by amaurer           #+#    #+#             */
/*   Updated: 2015/06/02 20:55:46 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

void	gfx_client_connect(t_client *client)
{
	char	str[200] = { 0 };

	snprintf(str, 200, "* %u %s %u %u %u", client->id, client->team->name,
		client->position->x, client->position->y, client->orientation);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_disconnect(t_client *client)
{
	char	str[20] = { 0 };

	snprintf(str, 20, "_ %u", client->id);
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

void	gfx_tile_remove(t_client *client, t_tile *tile, int item)
{
	char	str[20] = { 0 };

	snprintf(str, 20, "- %u %u %i", tile->x, tile->y, item);
	if (client == NULL)
		network_send(NULL, str, NET_SEND_GFX);
	else
		network_send(client, str, 0);
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
