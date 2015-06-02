/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/21 01:02:58 by amaurer           #+#    #+#             */
/*   Updated: 2015/06/02 00:01:13 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>

short	command_move(t_client *client, t_uint argc, char **argv)
{
	if (client->status != STATUS_PLAYER || argc != 1)
		return (COMMAND_FAIL);
	client_move(client);
	(void)argv;
	return (COMMAND_SUCCESS);
}

short	command_left(t_client *client, t_uint argc, char **argv)
{
	if (client->status != STATUS_PLAYER || argc != 1)
		return (COMMAND_FAIL);
	client_rotate(client, TURN_LEFT);
	(void)argv;
	return (COMMAND_SUCCESS);
}

short	command_right(t_client *client, t_uint argc, char **argv)
{
	if (argc != 1)
		return (COMMAND_FAIL);
	client_rotate(client, TURN_RIGHT);
	(void)argv;
	return (COMMAND_SUCCESS);
}

short	command_pause(t_client *client, t_uint argc, char **argv)
{
	if (client->status != STATUS_GFX || argc != 1)
		return (COMMAND_FAIL);
	zappy_pause(client);
	(void)argv;
	return (COMMAND_NONE);
}

short	command_resume(t_client *client, t_uint argc, char **argv)
{
	if (client->status != STATUS_GFX || argc != 1)
		return (COMMAND_FAIL);
	zappy_resume(client);
	(void)argv;
	return (COMMAND_NONE);
}

short	command_pick(t_client *client, t_uint argc, char **argv)
{
	if (client->status != STATUS_PLAYER || argc != 2)
		return (COMMAND_FAIL);
	if (client_pick(client, atoi(argv[1])))
		return (COMMAND_SUCCESS);
	return (COMMAND_FAIL);
}

short	command_drop(t_client *client, t_uint argc, char **argv)
{
	if (client->status != STATUS_PLAYER || argc != 2)
		return (COMMAND_FAIL);
	if (client_drop(client, atoi(argv[1])))
		return (COMMAND_SUCCESS);
	return (COMMAND_FAIL);
}

short	command_inventory(t_client *client, t_uint argc, char **argv)
{
	char	str[200] = { 0 };

	if (client->status != STATUS_PLAYER || argc != 1)
		return (COMMAND_FAIL);
	snprintf(str, 200, "food %u, linemate %u, deraumere %u, sibur %u, "
		"mendiane %u, phiras %u, thystame %u",
		client->items[0],
		client->items[1],
		client->items[2],
		client->items[3],
		client->items[4],
		client->items[5],
		client->items[6]
	);
	network_send(client, str, 0);
	(void)argv;
	return (COMMAND_NONE);
}

short	command_connect_count(t_client *client, t_uint argc, char **argv)
{
	size_t	client_count;
	char	str[4] = { 0 };

	if (client->status != STATUS_PLAYER || argc != 1)
		return (COMMAND_FAIL);
	client_count = team_clients_count(client->team);
	snprintf(str, 4, "%lu", client->team->max_clients - client_count);
	network_send(client, str, 0);
	(void)argv;
	return (COMMAND_NONE);
}
