/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/21 01:02:58 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/31 17:40:45 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>

short	command_move(t_client *client, t_uint argc, char **argv)
{
	if (client->gfx != 0 || argc != 1)
		return (0);
	client_move(client);
	(void)argv;
	return (1);
}

short	command_left(t_client *client, t_uint argc, char **argv)
{
	if (client->gfx != 0 || argc != 1)
		return (0);
	client_rotate(client, TURN_LEFT);
	(void)argv;
	return (1);
}

short	command_right(t_client *client, t_uint argc, char **argv)
{
	if (argc != 1)
		return (0);
	client_rotate(client, TURN_RIGHT);
	(void)argv;
	return (1);
}

short	command_pause(t_client *client, t_uint argc, char **argv)
{
	if (client->gfx == 0 || argc != 1)
		return (0);
	zappy_pause(client);
	(void)argv;
	return (-1);
}

short	command_resume(t_client *client, t_uint argc, char **argv)
{
	if (client->gfx == 0 || argc != 1)
		return (0);
	zappy_resume(client);
	(void)argv;
	return (-1);
}

short	command_pick(t_client *client, t_uint argc, char **argv)
{
	if (client->gfx != 0 || argc != 2)
		return (0);
	if (client_pick(client, atoi(argv[1])))
		return (1);
	return (0);
}

short	command_drop(t_client *client, t_uint argc, char **argv)
{
	if (client->gfx != 0 || argc != 2)
		return (0);
	if (client_pick(client, atoi(argv[1])))
		return (1);
	return (0);
}