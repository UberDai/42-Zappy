/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/21 01:44:26 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/30 19:50:48 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>
#include <stdlib.h>

static void	free_command(char **command)
{
	t_uint	i;

	i = 0;
	while (command[i])
	{
		free(command[i]);
		i++;
	}
	free(command);
}

short	client_queue_push(t_client *client, t_command *command, char **av)
{
	t_uint	i;

	i = 0;
	while (i < CLIENT_QUEUE_MAX && client->queue[i].set)
		i++;
	if (i == CLIENT_QUEUE_MAX)
		return (0);

	client->queue[i].set = 1;
	client->queue[i].ac = ft_splits_count(av);
	client->queue[i].av = av;
	client->queue[i].command = command;
	client->queue[i].delay = command->delay;
	return (1);
}

void	client_queue_shift(t_client *client)
{
	t_uint	i;

	if (client->queue[0].av != NULL)
		free_command(client->queue[0].av);
	i = 0;
	while (i < CLIENT_QUEUE_MAX)
	{
		if (i == CLIENT_QUEUE_MAX - 1)
			bzero(client->queue + i, sizeof(t_queue));
		else
			memcpy(client->queue + i, client->queue + i + 1,
				sizeof(t_queue));
		i++;
	}
}

void	client_queue_execute(t_client *client)
{
	t_queue	*queue;

	queue = &(client->queue[0]);
	if (!queue->set)
		return ;
	queue->delay--;

	if (queue->delay == 0)
		queue->command->func(client, 0, queue->av);
}

void	client_queue_free(t_client *client)
{
	t_uint	i;

	i = 0;
	while (i < CLIENT_QUEUE_MAX)
	{
		client_queue_shift(client);
		i++;
	}
}