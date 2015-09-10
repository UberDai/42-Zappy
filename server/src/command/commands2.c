/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/10 21:01:45 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 21:02:00 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

short	command_fork(t_client *client, t_uint argc, char **argv)
{
	if (client->status != STATUS_PLAYER || argc != 1)
		return (COMMAND_FAIL);
	egg_create(client);
	(void)argv;
	return (COMMAND_SUCCESS);
}

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
	if (client->status != STATUS_PLAYER || argc != 1)
		return (COMMAND_FAIL);
	client_rotate(client, TURN_RIGHT);
	(void)argv;
	return (COMMAND_SUCCESS);
}

short	command_expulse(t_client *client, t_uint argc, char **argv)
{
	if (client->status != STATUS_PLAYER || argc != 1)
		return (COMMAND_FAIL);
	client_expulse(client);
	(void)argv;
	return (COMMAND_SUCCESS);
}
