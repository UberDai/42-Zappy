/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/21 01:02:58 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 21:02:09 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>
#include <string.h>

short	command_connect_count(t_client *client, t_uint argc, char **argv)
{
	size_t	client_count;
	char	str[4];

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
	int			i;

	if ((i = 0) || client->status != STATUS_PLAYER || argc != 1)
		return (COMMAND_FAIL);
	str = strdup("{");
	vision = get_vision(client);
	init_iter(&iter, vision, increasing);
	while (++i >= 0 && lst_iterator_next(&iter))
	{
		content = tile_content(iter.data, client);
		str = append_string(str, content);
		free(content);
		if (i != (int)vision->size - 1)
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
	if (client->status != STATUS_PLAYER || argc != 1)
		return (COMMAND_FAIL);
	if (client_can_promote(client))
	{
		network_send(client, "elevation en cours", 0);
		return (COMMAND_SUCCESS);
	}
	network_send(client, NET_FAILURE, 0);
	(void)argv;
	return (COMMAND_FAIL);
}

short	command_promote(t_client *client, t_uint argc, char **argv)
{
	char	str[18];

	if (client->status != STATUS_PLAYER || argc != 1)
		return (COMMAND_FAIL);
	if (client_promote(client))
	{
		snprintf(str, 18, "niveau actuel : %u", client->level + 1);
		network_send(client, str, 0);
		return (COMMAND_NONE);
	}
	(void)argv;
	return (COMMAND_FAIL);
}
