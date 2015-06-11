/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/07 21:53:39 by amaurer           #+#    #+#             */
/*   Updated: 2015/06/11 23:52:07 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int	get_sound_direction(double *points)
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

void	client_hear(t_client *receiver, t_client *emitter, char *message)
{
	double	points[9][4];
	int		x1;
	int		x2;
	int		y1;
	int		y2;

	x1 = emitter->position->x;
	y1 = emitter->position->y;
	x2 = receiver->position->x;
	y2 = receiver->position->y;

	if (x1 == x2 && y1 == y2)
	{
		send_broadcast(receiver, 0, message);
		return ;
	}

	points[0][0] = x1;
	points[0][1] = y1;
	points[0][2] = x2;
	points[0][3] = y2;

	points[1][0] = x1;
	points[1][1] = y1;
	points[1][2] = x2 + (int)g_zappy.width;
	points[1][3] = y2;

	points[2][0] = x1;
	points[2][1] = y1;
	points[2][2] = x2 - (int)g_zappy.width;
	points[2][3] = y2;

	points[3][0] = x1;
	points[3][1] = y1;
	points[3][2] = x2;
	points[3][3] = y2 + (int)g_zappy.height;

	points[4][0] = x1;
	points[4][1] = y1;
	points[4][2] = x2;
	points[4][3] = y2 - (int)g_zappy.height;

	points[5][0] = x1;
	points[5][1] = y1;
	points[5][2] = x2 + (int)g_zappy.width;
	points[5][3] = y2 + (int)g_zappy.height;

	points[6][0] = x1;
	points[6][1] = y1;
	points[6][2] = x2 + (int)g_zappy.width;
	points[6][3] = y2 - (int)g_zappy.height;

	points[7][0] = x1;
	points[7][1] = y1;
	points[7][2] = x2 - (int)g_zappy.width;
	points[7][3] = y2 + (int)g_zappy.height;

	points[8][0] = x1;
	points[8][1] = y1;
	points[8][2] = x2 - (int)g_zappy.width;
	points[8][3] = y2 - (int)g_zappy.height;

	t_uint	i;
	double	min;
	double	distance;
	int		index;

	index = -1;
	min = (t_uint)-1;
	i = 0;
	while (i < 9)
	{
		distance = sqrt(pow(points[i][2] - points[i][0], 2) + pow(points[i][3] - points[i][1], 2));
		if (distance < min)
		{
			index = i;
			min = distance;
		}
		i++;
	}

	int orientation;

	orientation = get_sound_direction(points[index]);
	// orientation = (orientation + receiver->orientation) % 8 + 1;

	send_broadcast(receiver, orientation, message);
}

void	client_broadcast(t_client *emitter, char *message)
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
}
