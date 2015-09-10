/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zappy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 16:46:07 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 19:44:38 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <string.h>

void			zappy_pause(t_client *client)
{
	g_zappy.paused = 1;
	printf("Paused.");
	network_send(client, "pause", NET_SEND_ALL);
}

void			zappy_resume(t_client *client)
{
	g_zappy.paused = 0;
	network_send(client, "resume", NET_SEND_ALL);
	printf("Resumed.");
}

void			zappy_run(void)
{
	network_bind();
	g_zappy.time.next_cycle = get_time() + g_zappy.time.clock;
	while (1)
	{
		network_receive();
		g_zappy.time.next_cycle = get_time() + g_zappy.time.clock;
		if (!g_zappy.paused)
		{
			printf("\n---[ Cycle %02u ]-----------------------------------\n",
				g_zappy.time.cycle_count);
			if (g_zappy.time.cycle_count % REGEN_RATE == 0)
				map_regenerate();
			watch_eggs();
			clients_play();
			g_zappy.time.cycle_count++;
			printf("Clients ?: %lu  P: %lu  G: %lu\n",
				g_zappy.anonymous_clients->size,
				g_zappy.clients->size,
				g_zappy.gfx_clients->size);
			printf("--------------------------------------------------\n");
		}
	}
}
