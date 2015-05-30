/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/21 00:33:28 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/30 21:19:58 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include "dlist.h"
#include <libft.h>

t_command	g_commands[] = {
	{ "move", 0, command_move },
	{ "left", 0, command_left },
	{ "right", 0, command_right },
	{ "pause", 0, command_pause },
	{ "resume", 0, command_resume },
	{ NULL, 0, NULL }
};

static void			move_client_to_list(t_client *client, t_client **list)
{
	g_zappy.anonymous_clients = DLIST(remove, t_client *, client);

	if (*list == NULL)
		*list = client;
	else
		DLIST(append, void, (*list), (t_dlist*)client);
}

static t_client		*authenticate_gfx_client(t_client *client)
{
	t_client	*client2;
	char		str[20];

	client2 = (t_client*)DLIST_PREV(client);
	if (client2 == NULL)
		g_zappy.clients = NULL;

	move_client_to_list(client, &(g_zappy.gfx_clients));

	client->authenticated = 1;
	client->gfx = 1;
	client->position = NULL;

	snprintf(str, 20, "%u %u", g_zappy.width, g_zappy.height);
	network_send(client, str, 0);
	snprintf(str, 20, "%u", g_zappy.time.cycle_duration);
	network_send(client, str, 0);

	return (client2);
}

static t_client	*authenticate(t_client *client, char *input)
{
	t_team	*team;
	char	str[20];
	size_t	client_count;

	if (strcmp(input, "g") == 0)
		return authenticate_gfx_client(client);

	team = team_get(input);
	if (team == NULL)
	{
		network_send(client, "m8 dat team doesnt exist ya fool", 0);
		return (client);
	}
	client_count = team_clients_count(team);
	if (client_count >= team->max_clients)
	{
		network_send(client, "clubs full buddy, gtfo", 0);
		return network_client_disconnect(client);
	}

	client->team = team;
	client->authenticated = 1;

	move_client_to_list(client, &(g_zappy.clients));

	client_set_team(client, input);
	snprintf(str, 20, "%lu", team->max_clients - client_count);
	network_send(client, str, 0);
	snprintf(str, 20, "%u %u", g_zappy.width, g_zappy.height);
	network_send(client, str, 0);

	gfx_client_connect(client);

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
			if (client->gfx)
				g_commands[i].func(client, split_count, splits);
			else if (!client_queue_push(client, &(g_commands[i]), splits))
				network_send(client, "shits too fast", 0);
			return (client);
		}
		i++;
	}

	network_send(client, "dunno dat command lol", 0);
	return (client);
}
