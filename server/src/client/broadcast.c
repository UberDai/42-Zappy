/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/07 21:53:39 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 20:30:10 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define POINT(I, X1, Y1, X2, Y2) p[I][0]=X1;p[I][1]=Y1;p[I][2]=X2;p[I][3]=Y2

static void	send_broadcast(t_client *receiver, int direction, char *message)
{
	char	*str;
	size_t	size;

	size = strlen(message) + strlen("message ") + 5;
	str = calloc(size + 1, sizeof(char));
	snprintf(str, size, "message %u,%s", direction, message);
	network_send(receiver, str, 0);
	free(str);
}

static void	set_points(t_client *receiver, t_client *emitter, double *points)
{
	double	p[9][4];
	int		x1;
	int		x2;
	int		y1;
	int		y2;

	x1 = emitter->position->x;
	y1 = emitter->position->y;
	x2 = receiver->position->x;
	y2 = receiver->position->y;
	POINT(0, x1, y1, x2, y2);
	POINT(1, x1, y1, x2 + (int)g_zappy.width, y2);
	POINT(2, x1, y1, x2 - (int)g_zappy.width, y2);
	POINT(3, x1, y1, x2, y2 + (int)g_zappy.height);
	POINT(4, x1, y1, x2, y2 - (int)g_zappy.height);
	POINT(5, x1, y1, x2 + (int)g_zappy.width, y2 + (int)g_zappy.height);
	POINT(6, x1, y1, x2 + (int)g_zappy.width, y2 - (int)g_zappy.height);
	POINT(7, x1, y1, x2 - (int)g_zappy.width, y2 + (int)g_zappy.height);
	POINT(8, x1, y1, x2 - (int)g_zappy.width, y2 - (int)g_zappy.height);
	memcpy(points, p, sizeof(double) * 9 * 4);
}

static int	get_shortest_way(double (*p)[9][4])
{
	t_uint	i;
	double	min;
	double	distance;
	int		index;

	index = -1;
	min = (t_uint)-1;
	i = 0;
	while (i < 9)
	{
		distance = sqrt(pow(p[i][2] - p[i][0], 2) + pow(p[i][3] - p[i][1], 2));
		if (distance < min)
		{
			index = i;
			min = distance;
		}
		i++;
	}
	return (index);
}

void		client_hear(t_client *receiver, t_client *emitter, char *message)
{
	double	p[9][4];
	int		index;
	int		orientation;

	if (emitter->position->x == receiver->position->x
		&& emitter->position->y == receiver->position->y)
	{
		send_broadcast(receiver, 0, message);
		return ;
	}
	set_points(receiver, emitter, (double*)p);
	index = get_shortest_way((double (*)[9][4])p);
	orientation = get_direction(p[index]);
	orientation = orientation - (receiver->orientation - 1) * 2;
	if (orientation < 0)
		orientation += 8;
	send_broadcast(receiver, orientation, message);
}

void		client_broadcast(t_client *emitter, char *message)
{
	t_lstiter	iter;
	t_client	*receiver;

	init_iter(&iter, g_zappy.clients, increasing);
	while (lst_iterator_next(&iter))
	{
		receiver = iter.data;
		if (receiver != emitter)
			client_hear(receiver, emitter, message);
	}
	gfx_broadcast(emitter);
}
