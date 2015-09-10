/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/10 21:02:21 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 21:06:06 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <string.h>
#include <stdlib.h>

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
	free(str);
	(void)argv;
	return (COMMAND_NONE);
}
