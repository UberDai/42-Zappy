/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 22:02:12 by amaurer           #+#    #+#             */
/*   Updated: 2015/06/03 00:19:47 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

short	client_move_to(t_client *client, t_tile *tile)
{
	if (client->position != NULL)
	{
		client->position->client_count--;
		client->position->refresh_client_list = 1;
	}
	tile->client_count++;
	tile->refresh_client_list = 1;
	client->position = tile;
	gfx_client_move_to(client, client->position);
	return (1);
}

short	client_move(t_client *client)
{
	int		x;
	int		y;

	x = client->position->x;
	y = client->position->y;

	if (client->orientation == ORIENT_NORTH)
		y--;
	else if (client->orientation == ORIENT_SOUTH)
		y++;
	else if (client->orientation == ORIENT_WEST)
		x--;
	else if (client->orientation == ORIENT_EAST)
		x++;
	client_move_to(client, tile_at(x, y));
	return (1);
}

short	client_rotate(t_client *client, short angle)
{
	if (angle == TURN_LEFT)
		client->orientation -= 1;
	else if (angle == TURN_RIGHT)
		client->orientation += 1;
	else
		return (0);

	if (client->orientation <= 0)
		client->orientation = 4;
	else if (client->orientation >= 5)
		client->orientation = 1;
	gfx_client_turn(client);
	return (1);
}