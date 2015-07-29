/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 22:01:38 by amaurer           #+#    #+#             */
/*   Updated: 2015/07/29 03:09:57 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>

t_uint		g_promotion_needs[MAX_LEVEL][ITEM_COUNT] = {
	{ 1, 1, 0, 0, 0, 0, 0 },
	{ 2, 1, 1, 1, 0, 0, 0 },
	{ 2, 2, 0, 1, 0, 2, 0 },
	{ 4, 1, 1, 2, 0, 1, 0 },
	{ 4, 1, 2, 1, 3, 0, 0 },
	{ 6, 1, 2, 3, 0, 1, 0 },
	{ 6, 2, 2, 2, 2, 2, 1 }
};

short		client_can_promote(t_client *client)
{
	t_uint		i;
	t_lstiter	iter;
	t_tile		*tile;

	if (client->level >= MAX_LEVEL - 1)
		return (0);

	tile = client->position;

	if (tile->clients.size < g_promotion_needs[client->level][0])
		return (0);
	init_iter(&iter, &tile->clients, increasing);
	while (lst_iterator_next(&iter))
	{
		if (((t_client*)iter.data)->level != client->level)
			return (0);
	}
	i = 1;
	while (i < ITEM_COUNT)
	{
		if (g_promotion_needs[client->level][i] > tile->items[i])
			return (0);
		i++;
	}
	return (1);
}

short		client_promote(t_client *client)
{
	t_tile		*tile;
	t_lstiter	iter;
	t_uint		i;

	tile = client->position;
	if (!client_can_promote(client))
		return (0);

	i = 1;
	while (i < ITEM_COUNT)
	{
		tile->items[i] -= g_promotion_needs[client->level][i];
		i++;
	}
	init_iter(&iter, &tile->clients, increasing);
	while (lst_iterator_next(&iter))
		((t_client*)iter.data)->level++;

	network_send(client, ft_itoa(client->level), 0);
	return (1);
}
