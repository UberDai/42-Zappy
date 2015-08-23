/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/16 22:44:34 by amaurer           #+#    #+#             */
/*   Updated: 2015/08/23 12:44:52 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>
#include <stdlib.h>

t_client	*client_create()
{
	static t_uint	id;
	t_client		*client;

	if (id == 0)
		id = 1;
	client = calloc(1, sizeof(t_client));
	ft_bzero(client, sizeof(t_client));
	client->hunger = FOOD_DURATION;
	client->id = id++;
	client->items[ITEM_FOOD] = CLIENT_BASE_FOOD;
	client->sending_queue = new_lst();
	lst_push_back(g_zappy.anonymous_clients, client);
	return (client);
}

void	client_set_spawn_position(t_client *client)
{
	t_egg	*egg;

	client->orientation = rand() % 4 + 1;
	egg = get_hatched_egg(client->team);
	if (egg != NULL)
	{
		client_move_to(client, egg->position);
		egg_remove(egg);
	}
	else
	{
		client_move_to(client, tile_at(rand() % g_zappy.width, rand() % g_zappy.height));
	}
}

void	client_delete(t_client *client)
{
	if (client->status == STATUS_GFX)
		lst_remove(g_zappy.gfx_clients, lst_index_of(g_zappy.gfx_clients, client));
	else if (client->status == STATUS_UNKNOWN)
		lst_remove(g_zappy.anonymous_clients, lst_index_of(g_zappy.anonymous_clients, client));
	else
		lst_remove(g_zappy.clients, lst_index_of(g_zappy.clients, client));
	client_queue_free(client);
	lst_destroy(&client->sending_queue, free);
	free(client);
}

void	client_set_team(t_client *client, const char *team_name)
{
	t_team	*team;

	team = team_get(team_name);
	if (team == NULL)
		team = team_create(team_name);
	client->team = team;
}
