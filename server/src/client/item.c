/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/31 16:31:17 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/31 16:44:29 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <limits.h>

short	client_add_item(t_client *client, int item)
{
	if (item < 0 || item >= ITEM_COUNT)
		return (0);
	if (client->items[item] == UINT_MAX)
		return (0);
	client->items[item]++;
	return (1);
}

short	client_remove_item(t_client *client, int item)
{
	if (item < 0 || item >= ITEM_COUNT)
		return (0);
	if (client->items[item] == 0)
		return (0);
	client->items[item]--;
	return (1);
}

short	client_pick(t_client *client, int item)
{
	if (client_add_item(client, item))
	{
		if (tile_remove_item(client->position, item))
			return (1);
		client_remove_item(client, item);
	}
	return (0);
}

short	client_drop(t_client *client, int item)
{
	if (client_remove_item(client, item))
	{
		if (tile_add_item(client->position, item))
			return (1);
		client_add_item(client, item);
	}
	return (0);
}