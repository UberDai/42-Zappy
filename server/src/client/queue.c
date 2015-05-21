/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/21 01:44:26 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/21 03:12:14 by amaurer          ###   ########.fr       */
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

short	client_queue_push(t_client *client, char **command, t_uint delay)
{
	t_uint	i;

	i = 0;
	while (client->queue[i].set)
		i++;

	if (i == CLIENT_QUEUE_MAX)
		return (0);

	client->queue[i].set = 1;
	client->queue[i].command = command;
	client->queue[i].delay = delay;

	return (1);
}

void	client_queue_shift(t_client *client)
{
	t_uint	i;

	if (client->queue[0].command != NULL)
		free_command(client->queue[0].command);

	i = 0;
	while (i < CLIENT_QUEUE_MAX)
	{
		if (i == CLIENT_QUEUE_MAX - 1)
			bzero(client->queue + i, sizeof(t_queue));
		else
			ft_memcpy(client->queue + i, client->queue + i + 1, sizeof(t_queue));
		i++;
	}
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