/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/14 23:42:00 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 21:07:15 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>
#include <strings.h>
#include <limits.h>

void		map_init(void)
{
	t_uint	x;
	t_uint	y;

	g_zappy.map = calloc(g_zappy.height, sizeof(t_tile **));
	y = 0;
	while (y < g_zappy.height)
	{
		g_zappy.map[y] = calloc(g_zappy.width, sizeof(t_tile *));
		x = 0;
		while (x < g_zappy.width)
		{
			g_zappy.map[y][x] = tile_create(x, y);
			x++;
		}
		y++;
	}
}

void		map_regenerate(void)
{
	t_uint	x;
	t_uint	y;

	y = 0;
	while (y < g_zappy.height)
	{
		x = 0;
		while (x < g_zappy.width)
		{
			tile_regenerate(g_zappy.map[y][x]);
			x++;
		}
		y++;
	}
}

void		tile_regenerate(t_tile *tile)
{
	t_uint	i;
	t_uint	j;
	t_uint	amount;

	i = 0;
	while (i < ITEM_COUNT)
	{
		if (rand() % REGEN_PROBABILITY == 0)
		{
			amount = rand_range(0, REGEN_MAX);
			tile->items[i] += amount;
			j = 0;
			while (j < amount)
			{
				gfx_tile_add(NULL, tile, i);
				j++;
			}
		}
		i++;
	}
}

static int	get_direction_if(double x, double y, double slope)
{
	if (x < 0 && slope > -1 && slope < 1)
		return (1);
	if (x > 0 && slope > -1 && slope < 1)
		return (5);
	if ((slope < -1 || slope > 1 || x == 0) && y < 1)
		return (7);
	if ((slope < -1 || slope > 1 || x == 0) && y > 0)
		return (3);
	if (x < 0 && x == y)
		return (8);
	if (x < 0 && x == -y)
		return (2);
	if (x > 0 && x == y)
		return (4);
	if (x > 0 && x == -y)
		return (6);
	return (0);
}

int			get_direction(double *points)
{
	double	slope;
	char	vertical;
	double	x;
	double	y;

	x = points[1] - points[3];
	y = points[0] - points[2];
	if (x == 0)
	{
		slope = 0;
		vertical = 1;
	}
	else
	{
		slope = y / x;
		vertical = 0;
	}
	get_direction_if(x, y, slope);
	return (0);
}
