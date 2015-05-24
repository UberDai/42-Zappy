/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/21 00:33:28 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/25 01:54:05 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>
#include <stdio.h>

t_command	g_commands[] = {
	{ "move", 7, command_move },
	{ "left", 7, command_left },
	{ "right", 7, command_right },
	{ NULL, 0, NULL }
};

static t_client	*authenticate(t_client *client, char *input)
{
	t_team	*team;
	char	str[20];
	size_t	client_count;

	team = team_get(input);
	if (team == NULL)
	{
		network_send(client, "m8 dat team doesnt exist ya fool");
		return (client);
	}
	client_count = team_clients_count(team);
	if (client_count >= team->max_clients)
	{
		network_send(client, "clubs full buddy, gtfo");
		return network_client_disconnect(client);
	}
	client->team = team;
	client->authenticated = 1;
	client_set_team(client, input);
	snprintf(str, 20, "%lu", team->max_clients - client_count);
	network_send(client, str);
	snprintf(str, 20, "%u %u", g_zappy.width, g_zappy.height);
	network_send(client, str);
	return (client);
}

t_client	*command_parse(t_client *client, char *input)
{
	char	**splits;
	t_uint	split_count;
	t_uint	i;

	if (!client->authenticated)
		return authenticate(client, input);

	splits = ft_strsplit(input, ' ');
	split_count = ft_splits_count(splits);

	i = 0;
	while (g_commands[i].name != NULL)
	{
		if (ft_strcmp(g_commands[i].name, splits[0]) == 0)
		{
			if (!client_queue_push(client, &(g_commands[i]), splits))
				network_send(client, "shits too fast");
			print_client_queue(client);
			return (client);
		}
		i++;
	}

	network_send(client, "dunno dat command lol");
	return (client);
}