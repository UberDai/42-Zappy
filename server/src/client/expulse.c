
#include "zappy.h"
#include <stdio.h>

static void	client_get_expulsed(t_client *client, const t_tile *position)
{
	double	points[4];
	char	message[14] = { 0 };

	points[0] = client->position->x;
	points[1] = client->position->y;
	points[2] = position->x;
	points[3] = position->y;
	sprintf(message, 14, "deplacement %i", get_direction(points));
	network_send(client, message, 0);
	client->position = position;
}

void	client_expulse(const t_client *client)
{
	t_tile		*tile;
	t_lstiter	iter;
	t_client	*target;

	tile = client->position;
	if (client->orientation == ORIENT_NORTH)
		tile = tile_at(tile->x - 1, tile->y);
	else if (client->orientation == ORIENT_SOUTH)
		tile = tile_at(tile->x + 1, tile->y);
	else if (client->orientation == ORIENT_EAST)
		tile = tile_at(tile->x, tile->y + 1);
	else if (client->orientation == ORIENT_WEST)
		tile = tile_at(tile->x, tile->y - 1);

	init_iter(&iter, client->position->clients, increasing);
	while (lst_iterator_next(&iter))
	{
		target = (t_client*)iter.data;
		if (target == client)
			continue ;
		client_get_expulsed(target, tile);
	}
}
