/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/21 01:02:58 by amaurer           #+#    #+#             */
/*   Updated: 2015/08/13 01:13:49 by amaurer          ###   ########.fr       */
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
	int		item;
	t_uint	i;

	if (client->status != STATUS_PLAYER || argc != 2)
		return (COMMAND_FAIL);

	i = 0;
	item = -1;
	while (i < ITEM_COUNT)
	{
		if (strcmp(argv[1], g_item_names[i]) == 0)
		{
			item = i;
			break ;
		}
		i++;
	}

	if (item != -1 && client_pick(client, item))
		return (COMMAND_SUCCESS);
	return (COMMAND_FAIL);
}

short	command_drop(t_client *client, t_uint argc, char **argv)
{
	int		item;
	t_uint	i;

	if (client->status != STATUS_PLAYER || argc != 2)
		return (COMMAND_FAIL);
	i = 0;
	item = -1;
	while (i < ITEM_COUNT)
	{
		if (strcmp(argv[1], g_item_names[i]) == 0)
		{
			item = i;
			break ;
		}
		i++;
	}
	if (item != -1 && client_drop(client, item))
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
		content = tile_content(iter.data, client);
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
	char		*message;
	t_uint		i;
	size_t		size;

	if (client->status != STATUS_PLAYER)
		return (COMMAND_FAIL);
	i = 1;
	size = 0;
	while (i < argc)
	{
		size += strlen(argv[i]) + 1;
		i++;
	}
	message = calloc(size, sizeof(char));
	i = 1;
	while (i < argc)
	{
		strcat(message, argv[i]);
		if (i != argc - 1)
			strcat(message, " ");
		i++;
	}
	client_broadcast(client, message);
	free(message);
	return (COMMAND_SUCCESS);
}

short	command_pre_promote(t_client *client, t_uint argc, char **argv)
{
	t_uint	current_level;
	t_lstiter	iter;

	if (client->status != STATUS_PLAYER || argc != 1)
		return (COMMAND_FAIL);

	if (client_can_promote(client))
	{
		current_level = client->level;
		init_iter(&iter, &client->position->clients, increasing);
		while (lst_iterator_next(&iter))
		{
			if (client->level == current_level)
				network_send((t_client*)iter.data, "elevation en cours", 0);
		}
		return (COMMAND_SUCCESS);
	}

	network_send(client, NET_FAILURE, 0);

	(void)argv;
	return (COMMAND_FAIL);
}

short	command_promote(t_client *client, t_uint argc, char **argv)
{
	char	str[18] = { 0 };
	t_uint	current_level;
	t_lstiter	iter;

	if (client->status != STATUS_PLAYER || argc != 1)
		return (COMMAND_FAIL);

	if (client_promote(client))
	{
		snprintf(str, 18, "niveau actuel : %u", client->level + 1);

		current_level = client->level;
		init_iter(&iter, &client->position->clients, increasing);
		while (lst_iterator_next(&iter))
		{
			if (client->level == current_level)
				network_send(client, str, 0);
		}
		return (COMMAND_NONE);
	}

	(void)argv;
	return (COMMAND_FAIL);
}
