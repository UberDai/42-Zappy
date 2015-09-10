/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/10 19:40:43 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 20:10:16 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

static short	client_hunger(t_client *client)
{
	if (client->hunger == 0)
	{
		if (client->items[ITEM_FOOD] > 0)
		{
			client->items[ITEM_FOOD]--;
			client->hunger = FOOD_DURATION;
		}
		else
		{
			network_send(client, "mort", 0);
			gfx_client_death(client);
			network_client_disconnect(client);
			return (0);
		}
	}
	else
		client->hunger--;
	return (1);
}

static short	client_play(t_client *client)
{
	t_queue		*queue;
	int			ret;

	queue = &(client->queue[0]);
	if (client_hunger(client) == 0)
		return (1);
	if (!queue->set)
		return (0);
	if (queue->delay == 0)
	{
		ret = queue->command->func(client, queue->ac, queue->av);
		if (ret == 1)
			network_send(client, NET_SUCCESS, 0);
		else if (ret == 0)
			network_send(client, NET_FAILURE, 0);
		client_queue_shift(client);
	}
	else if (queue->delay == queue->command->delay && queue->command->pre_func)
	{
		ret = queue->command->pre_func(client, queue->ac, queue->av);
		if (ret == COMMAND_FAIL)
			client_queue_shift(client);
	}
	queue->delay--;
	client->hunger--;
	return (0);
}

void			clients_play(void)
{
	t_client	*client;
	size_t		i;

	i = 0;
	while (i < g_zappy.clients->size)
	{
		client = (t_client*)lst_data_at(g_zappy.clients, i);
		if (client_play(client) == 0)
			i++;
	}
}
