/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 22:02:12 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/19 22:17:09 by amaurer          ###   ########.fr       */
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
	client->orientation %= 3;
	return (1);
}

short	client_move(t_client *client)
{
	t_tile	*tile;

	tile = g_zappy.map[client->position->x][client->position->y];
	return client_move_to(client, tile);
}