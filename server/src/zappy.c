/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zappy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 16:46:07 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/29 20:40:22 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

void	zappy_pause(t_client *client)
{
	g_zappy.paused = 1;
	network_send(client, "pause", NET_SEND_ALL);
}

void	zappy_resume(t_client *client)
{
	g_zappy.paused = 0;
	network_send(client, "resume", NET_SEND_ALL);
}

static void	client_play(t_client *client)
{
	t_queue	*queue;

	print_client_queue(client);

	queue = &(client->queue[0]);

	if (!queue->set)
		return ;

	queue->delay--;

	if (queue->delay == 0)
	{
		queue->func(client, queue->ac, queue->av);
		client_queue_shift(client);
	}
}

static void	clients_play(void)
{
	t_client	*client;

	client = g_zappy.clients;
	while (client)
	{
		client_play(client);
		client = client->next;
	}
}

void	zappy_run(void)
{
	network_bind();
	g_zappy.time.next_cycle = get_time() + g_zappy.time.clock;
	while (1)
	{
		printf("[ Cycle %u ]\n", g_zappy.time.cycle_count);
		network_receive();
		g_zappy.time.next_cycle = get_time() + g_zappy.time.clock;
		if (!g_zappy.paused)
		{
			clients_play();
			g_zappy.time.cycle_count++;
		}
	}
}