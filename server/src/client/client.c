/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/16 22:44:34 by amaurer           #+#    #+#             */
/*   Updated: 2015/07/29 02:33:59 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>
#include <stdlib.h>

t_client	*client_create()
{
	static t_uint	id;
	t_client		*client;
	t_tile			*tile;

	if (id == 0)
		id = 1;
	client = calloc(1, sizeof(t_client));
	ft_bzero(client, sizeof(t_client));
	client->hunger = FOOD_DURATION;
	client->id = id++;
	client->orientation = ORIENT_NORTH;
	client->items[ITEM_FOOD] = CLIENT_BASE_FOOD;
	tile = tile_at(rand() % g_zappy.width, rand() % g_zappy.height);
	client_move_to(client, tile);
	lst_push_back(g_zappy.anonymous_clients, client);
	return (client);
}

void	client_delete(t_client *client_to_delete)
{
	if (client_to_delete->status == STATUS_GFX)
		lst_remove(g_zappy.gfx_clients, lst_index_of(g_zappy.gfx_clients, client_to_delete));
	else if (client_to_delete->status == STATUS_UNKNOWN)
		lst_remove(g_zappy.anonymous_clients, lst_index_of(g_zappy.anonymous_clients, client_to_delete));
	else
	{
		lst_remove(g_zappy.clients, lst_index_of(g_zappy.clients, client_to_delete));
	}
	client_queue_free(client_to_delete);
	free(client_to_delete);
}

void	client_set_team(t_client *client, const char *team_name)
{
	t_team	*team;

	team = team_get(team_name);
	if (team == NULL)
		team = team_create(team_name);
	client->team = team;
}
