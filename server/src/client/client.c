/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/16 22:44:34 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/21 02:50:55 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>
#include <stdlib.h>

t_client	*client_create(t_tile *position)
{
	static t_uint	id;
	t_client		*client;
	t_client		*clients;

	if (id == 0)
		id = 1;
	client = malloc(sizeof(t_client));
	ft_bzero(client, sizeof(t_client));
	client->hunger = FOOD_DURATION;
	client->id = id++;
	client->life = CLIENT_BASE_LIFE;
	client_move_to(client, position);
	clients = g_zappy.clients;
	if (clients == NULL)
		g_zappy.clients = client;
	else
	{
		while (clients->next)
			clients = clients->next;
		clients->next = client;
	}
	return (client);
}

void	client_delete(t_client *client_to_delete)
{
	t_client	*client;

	client = g_zappy.clients;
	if (client == client_to_delete)
		g_zappy.clients = client->next;
	else
	{
		while (client && client->next == client_to_delete)
			client = client->next;

		if (client == NULL)
			return ;

		client->next = client_to_delete->next;
	}
	client_to_delete->position->client_count--;
	client_queue_free(client);
	free(client_to_delete);
}