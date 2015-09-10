/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expulse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/16 22:50:24 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 20:11:03 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdio.h>

static void	client_get_expulsed(t_client *client, t_tile *position)
{
	double	points[4];
	char	message[14];
	int		orientation;

	points[0] = client->position->x;
	points[1] = client->position->y;
	points[2] = position->x;
	points[3] = position->y;
	orientation = get_direction(points) - (client->orientation - 1) * 2;
	if (orientation < 0)
		orientation += 8;
	snprintf(message, 14, "deplacement %i", orientation);
	network_send(client, message, 0);
	client_move_to(client, position);
	client_queue_free(client);
}

void		client_expulse(const t_client *client)
{
	t_tile		*tile;
	t_lstiter	iter;
	t_client	*target;

	tile = client->position;
	if (client->orientation == ORIENT_NORTH)
		tile = tile_at(tile->x, tile->y - 1);
	else if (client->orientation == ORIENT_SOUTH)
		tile = tile_at(tile->x, tile->y + 1);
	else if (client->orientation == ORIENT_EAST)
		tile = tile_at(tile->x + 1, tile->y);
	else if (client->orientation == ORIENT_WEST)
		tile = tile_at(tile->x - 1, tile->y);
	init_iter(&iter, &client->position->clients, increasing);
	while (lst_iterator_next(&iter))
	{
		target = (t_client*)iter.data;
		if (target == client)
			continue ;
		client_get_expulsed(target, tile);
	}
}
