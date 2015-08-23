/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 00:03:39 by amaurer           #+#    #+#             */
/*   Updated: 2015/08/23 12:43:43 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <math.h>

#define LEVEL	(client->level + 1)

static void	rotate_90(int *x, int *y)
{
	int	x2;
	int	y2;

	x2 = *y;
	y2 = *x * -1;

	*x = x2;
	*y = y2;
}

static void	rotate_180(int *x, int *y)
{
	*x *= -1;
	*y *= -1;
}

static void	rotate_270(int *x, int *y)
{
	int	x2;
	int	y2;

	x2 = *y * -1;
	y2 = *x;

	*x = x2;
	*y = y2;
}

static void	rotate_coords(t_client *client, int *x, int *y)
{
	if (client->orientation == ORIENT_EAST)
		rotate_90(x, y);
	else if (client->orientation == ORIENT_NORTH)
		rotate_180(x, y);
	else if (client->orientation == ORIENT_WEST)
		rotate_270(x, y);
}

t_lst	*get_vision(t_client *client)
{
	t_lst	*list;
	int		row;
	int		col;
	int		x;
	int		y;

	list = new_lst();
	row = 0;
	while (row <= LEVEL)
	{
		col = -row;
		while (col <= row)
		{
			x = col;
			y = row;

			rotate_coords(client, &x, &y);
			x += client->position->x;
			y += client->position->y;
			lst_push_back(list, tile_at(x, y));
			col++;
		}
		row++;
	}
	return (list);
}
