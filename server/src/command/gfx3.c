/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/10 21:04:43 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 21:05:09 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>

void	gfx_tile_add(t_client *client, t_tile *tile, int item)
{
	char	str[20];

	snprintf(str, 20, "+ %u %u %i", tile->x, tile->y, item);
	if (client == NULL)
		network_send(NULL, str, NET_SEND_GFX);
	else
		network_send(client, str, 0);
}

void	gfx_egg_add(const t_egg *egg)
{
	char	str[100];

	snprintf(str, 10, "0 %s %u %u", egg->team->name, egg->position->x,
		egg->position->y);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_egg_remove(const t_egg *egg)
{
	char	str[100];

	snprintf(str, 10, "9 %s %u %u", egg->team->name, egg->position->x,
		egg->position->y);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_pick(t_client *client, int item)
{
	char	str[20];

	snprintf(str, 20, "^ %u %i", client->id, item);
	network_send(NULL, str, NET_SEND_GFX);
}

void	gfx_client_drop(t_client *client, int item)
{
	char	str[20];

	snprintf(str, 20, "v %u %i", client->id, item);
	network_send(NULL, str, NET_SEND_GFX);
}
