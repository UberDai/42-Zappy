/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/21 01:02:58 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/30 21:23:40 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>

short	command_move(t_client *client, t_uint argc, char **argv)
{
	t_tile	*tile;
	int		x;
	int		y;

	if (argc != 1)
		return (0);
	x = client->position->x;
	y = client->position->y;

	if (client->orientation == ORIENT_NORTH)
		y--;
	else if (client->orientation == ORIENT_SOUTH)
		y++;
	else if (client->orientation == ORIENT_WEST)
		x--;
	else if (client->orientation == ORIENT_EAST)
		x++;
	tile = tile_at(x, y);
	client_move_to(client, tile);
	(void)argc;
	(void)argv;
	return (1);
}

short	command_left(t_client *client, t_uint argc, char **argv)
{
	if (argc != 1)
		return (0);
	if (client->orientation == 4)
		client->orientation = 1;
	else
		client->orientation++;
	(void)argc;
	(void)argv;
	return (1);
}

short	command_right(t_client *client, t_uint argc, char **argv)
{
	if (argc != 1)
		return (0);
	if (client->orientation == 1)
		client->orientation = 4;
	else
		client->orientation--;
	(void)argc;
	(void)argv;
	return (1);
}

short	command_pause(t_client *client, t_uint argc, char **argv)
{
	if (client->gfx == 0)
		return (0);
	zappy_pause(client);
	(void)argc;
	(void)argv;
	return (1);
}

short	command_resume(t_client *client, t_uint argc, char **argv)
{
	if (client->gfx == 0)
		return (0);
	zappy_resume(client);
	(void)argc;
	(void)argv;
	return (1);
}