/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/21 01:02:58 by amaurer           #+#    #+#             */
/*   Updated: 2015/06/13 00:48:50 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>
#include <string.h>

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
	char	*str;

	if (client->status != STATUS_PLAYER || argc != 1)
		return (COMMAND_FAIL);
	str = client_inventory(client);
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
	client_count = team_count_clients(client->team);
	snprintf(str, 4, "%lu", client->team->max_clients - client_count);
	network_send(client, str, 0);
	(void)argv;
	return (COMMAND_NONE);
}

static char	*append_string(char *src, char *str)
{
	char	*output;

	output = calloc(strlen(src) + strlen(str) + 1, sizeof(char));
	memcpy(output, src, strlen(src));
	strcat(output, str);
	free(src);
	return (output);
}

short	command_see(t_client *client, t_uint argc, char **argv)
{
	char		*str;
	t_lst		*vision;
	t_lstiter	iter;
	char		*content;

	if (client->status != STATUS_PLAYER || argc != 1)
		return (COMMAND_FAIL);

	str = strdup("{");
	vision = get_vision(client);

	init_iter(&iter, vision, increasing);
	while (lst_iterator_next(&iter))
	{
		content = tile_content(iter.data);
		str = append_string(str, content);
		free(content);

		if (iter.pos != vision->size - 1)
			str = append_string(str, ", ");
	}
	str = append_string(str, "}");
	network_send(client, str, 0);
	free(str);
	lst_destroy(&vision, NULL);
	(void)argv;
	return (COMMAND_NONE);
}

short	command_broadcast(t_client *client, t_uint argc, char **argv)
{
	if (client->status != STATUS_PLAYER || argc != 2)
		return (COMMAND_FAIL);

	client_broadcast(client, argv[1]);
	return (COMMAND_SUCCESS);
}
