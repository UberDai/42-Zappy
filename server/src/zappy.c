/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zappy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 16:46:07 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/31 19:29:47 by amaurer          ###   ########.fr       */
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
	int		ret;

	print_client_queue(client);

	queue = &(client->queue[0]);

	if (!queue->set)
		return ;

	if (queue->delay == 0)
	{
		ret = queue->command->func(client, queue->ac, queue->av);
		if (ret == 1)
			network_send(client, NET_SUCCESS, 0);
		else if (ret == 0)
			network_send(client, NET_FAILURE, 0);
		client_queue_shift(client);
	}

	queue->delay--;
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
		printf("\n---[ Cycle %02u ]-----------------------------------\n", g_zappy.time.cycle_count);
		if (g_zappy.time.cycle_count % REGEN_RATE == 0)
			map_regenerate();
		network_receive();
		g_zappy.time.next_cycle = get_time() + g_zappy.time.clock;
		if (!g_zappy.paused)
		{
			clients_play();
			g_zappy.time.cycle_count++;
		}
		printf("Clients A: %lu  C: %lu  G: %lu\n",
			dlist_length((t_dlist*)g_zappy.anonymous_clients),
			dlist_length((t_dlist*)g_zappy.clients),
			dlist_length((t_dlist*)g_zappy.gfx_clients)
		);
		if (g_zappy.clients != NULL)
			print_client(g_zappy.clients);
		printf("--------------------------------------------------\n");
	}
}