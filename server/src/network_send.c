/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_send.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/10 21:08:45 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 21:08:52 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

static void	network_send_to_clients(t_client *emitter, t_lst *list,
	const char *str)
{
	t_lstiter	iter;
	t_client	*client;

	init_iter(&iter, list, increasing);
	while (lst_iterator_next(&iter))
	{
		client = (t_client*)iter.data;
		if (emitter == NULL || client != emitter)
			network_send(client, str, 0);
	}
}

void		network_send_team(const t_team *team, const char *str)
{
	t_lstiter	iter;
	t_client	*client;

	init_iter(&iter, g_zappy.clients, increasing);
	while (lst_iterator_next(&iter))
	{
		client = (t_client*)iter.data;
		if (client->team == team)
			network_send(client, str, 0);
	}
}

void		network_send(t_client *client, const char *str, int options)
{
	char		*output;

	if (options != 0)
	{
		if (options & (NET_SEND_CLIENT | NET_SEND_ALL))
			network_send_to_clients(client, g_zappy.clients, str);
		if (options & (NET_SEND_GFX | NET_SEND_ALL))
			network_send_to_clients(client, g_zappy.gfx_clients, str);
	}
	else
	{
		asprintf(&output, "%s\n", str);
		logger_client_send(client, output);
		lst_push_back(client->sending_queue, output);
	}
}
