/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/10 21:03:38 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 21:04:20 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdio.h>

void	gfx_client_connect(t_client *client, t_client *gfx_client)
{
	char	str[200];

	snprintf(str, 200, "* %u %s %u %u %u", client->id, client->team->name,
		client->position->x, client->position->y, client->orientation);
	if (gfx_client != NULL)
		network_send(gfx_client, str, 0);
	else
		network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_disconnect(t_client *client)
{
	char	str[20];

	snprintf(str, 20, "_ %u", client->id);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_promote(const t_client *client)
{
	char	str[6];

	snprintf(str, 6, "! %u", client->id);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_death(t_client *client)
{
	char	str[20];

	snprintf(str, 20, "x %u", client->id);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_victory(const t_team *team)
{
	char	str[23];

	snprintf(str, 23, "$ %s", team->name);
	network_send(NULL, str, NET_SEND_GFX);
}
