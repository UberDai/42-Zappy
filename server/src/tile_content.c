/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/10 19:11:25 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 19:55:41 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <string.h>
#include <stdlib.h>

static void	tile_content_append(char *str, const char *append)
{
	if (strlen(str) != 0)
		strcat(str, " ");
	strcat(str, append);
}

static void	tile_content_append_items(const t_tile *tile, char *str)
{
	t_uint	i;
	t_uint	j;

	i = 0;
	while (i < ITEM_COUNT)
	{
		j = 0;
		while (j < tile->items[i])
		{
			tile_content_append(str, g_item_names[i]);
			j++;
		}
		i++;
	}
}

char		*tile_content(t_tile *tile, t_client *client)
{
	char		*str;
	size_t		size;
	t_uint		i;

	i = 0;
	size = tile->clients.size * strlen("joueur ");
	while (i < ITEM_COUNT)
	{
		size += tile->items[i] * (strlen(g_item_names[i]) + 1);
		i++;
	}
	str = calloc(size, sizeof(char));
	tile_content_append_items(tile, str);
	i = 0;
	while (i < tile->clients.size)
	{
		if (lst_data_at(&(tile->clients), i) != client)
			tile_content_append(str, "joueur");
		i++;
	}
	return (str);
}
