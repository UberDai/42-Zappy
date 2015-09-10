/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/21 00:33:28 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 20:00:15 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>

t_command	g_commands[] = {
	{ "avance", 7, NULL, command_move },
	{ "gauche", 7, NULL, command_left },
	{ "droite", 7, NULL, command_right },
	{ "prend", 7, NULL, command_pick },
	{ "pose", 7, NULL, command_drop },
	{ "pause", 0, NULL, command_pause },
	{ "continuer", 0, NULL, command_resume },
	{ "inventaire", 1, NULL, command_inventory },
	{ "connect_nbr", 0, NULL, command_connect_count },
	{ "voir", 1, NULL, command_see },
	{ "broadcast", 1, NULL, command_broadcast },
	{ "incantation", 3, command_pre_promote, command_promote },
	{ "fork", 42, NULL, command_fork },
	{ "expulse", 7, NULL, command_expulse },
	{ NULL, 0, NULL, NULL }
};

static void	move_client_to_list(t_client *client, t_lst *from,
	t_lst *to)
{
	size_t	index;

	index = lst_index_of(from, client);
	lst_push_back(to, lst_remove(from, index));
}

static void	authenticate_gfx_client(t_client *client)
{
	char		str[20];

	move_client_to_list(client, g_zappy.anonymous_clients, g_zappy.gfx_clients);
	client->status = STATUS_GFX;
	client->position = NULL;
	snprintf(str, 20, "%u %u", g_zappy.width, g_zappy.height);
	network_send(client, str, 0);
	snprintf(str, 20, "%u", g_zappy.time.cycle_duration);
	network_send(client, str, 0);
	gfx_send_map(client);
	gfx_send_clients(client);
}

static char	authenticate(t_client *client, char *input)
{
	t_team	*team;
	char	str[100];
	size_t	client_count;

	if (strcmp(input, "g") == 0)
	{
		authenticate_gfx_client(client);
		return (1);
	}
	team = team_get(input);
	if (team == NULL)
	{
		network_send(client, "m8 dat team doesnt exist ya fool", 0);
		return (0);
	}
	client_count = team_count_clients(team);
	if (client_count >= team->max_clients)
	{
		network_send(client, "clubs full buddy", 0);
		network_client_disconnect(client);
		return (0);
	}
	client->team = team;
	client->status = STATUS_PLAYER;
	move_client_to_list(client, g_zappy.anonymous_clients, g_zappy.clients);
	client_set_team(client, input);
	client_set_spawn_position(client);
	snprintf(str, 100, "%lu\n%u %u", team->max_clients - client_count,
		g_zappy.width, g_zappy.height);
	network_send(client, str, 0);
	gfx_client_connect(client, NULL);
	return (0);
}

char		command_parse(t_client *client, char *input)
{
	char	**splits;
	t_uint	split_count;
	t_uint	i;

	if (client->status == STATUS_UNKNOWN)
		return (authenticate(client, input));
	splits = ft_strsplit(input, ' ');
	split_count = ft_splits_count(splits);
	i = 0;
	while (split_count > 0 && g_commands[i].name != NULL)
	{
		if (strcmp(g_commands[i].name, splits[0]) == 0)
		{
			if (client->status == STATUS_GFX)
				g_commands[i].func(client, split_count, splits);
			else if (!client_queue_push(client, &(g_commands[i]), splits))
				network_send(client, "shits too fast", 0);
			return (0);
		}
		i++;
	}
	network_send(client, "dunno dat command lol", 0);
	return (0);
}
