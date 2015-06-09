/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 00:03:39 by amaurer           #+#    #+#             */
/*   Updated: 2015/06/10 00:06:19 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

t_lst	*get_vision(t_client *client)
{
	t_lst	*list;
	t_uint	row;
	t_uint	line;
	int		x;
	int		y;

	list = new_lst();
	row = 0;
	while (row < (client->level + 1) + 1)
	{
		if (client->orientation == ORIENT_NORTH || client->orientation == ORIENT_EAST)
			y = client->position->y + row;
		else if (client->orientation == ORIENT_SOUTH || client->orientation == ORIENT_WEST)
			y = client->position->y - row;

		line = 0;
		while (line < row * 2 + 1)
		{
			if (client->orientation == ORIENT_NORTH || client->orientation == ORIENT_EAST)
				x = client->position->x + line - row;
			else if (client->orientation == ORIENT_SOUTH || client->orientation == ORIENT_WEST)
				x = client->position->x - line + row;
			if (client->orientation == ORIENT_NORTH || client->orientation == ORIENT_SOUTH)
			{
				// printf("[%u;%u]\t", tile_at(x, y)->x, tile_at(x, y)->y);
				lst_push_back(list, tile_at(x, y));
			}
			else if (client->orientation == ORIENT_EAST || client->orientation == ORIENT_WEST)
			{
				// printf("[%u;%u]\t", tile_at(y, x)->x, tile_at(y, x)->y);
				lst_push_back(list, tile_at(y, x));
			}
			line++;
		}
		printf("\n");
		row++;
	}

	return (list);
}