/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/07 21:53:39 by amaurer           #+#    #+#             */
/*   Updated: 2015/06/07 23:40:40 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <math.h>

void	client_hear(t_client *receiver, t_client *emitter)
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
		// provenance case 0
	}

	points[0][0] = x1;
	points[0][1] = y1;
	points[0][2] = x2;
	points[0][3] = y2;

	points[1][0] = x1;
	points[1][1] = y1;
	points[1][2] = x2 + 10;
	points[1][3] = y2;

	points[2][0] = x1;
	points[2][1] = y1;
	points[2][2] = x2 - 10;
	points[2][3] = y2;

	points[3][0] = x1;
	points[3][1] = y1;
	points[3][2] = x2;
	points[3][3] = y2 + 10;

	points[4][0] = x1;
	points[4][1] = y1;
	points[4][2] = x2;
	points[4][3] = y2 - 10;

	points[5][0] = x1;
	points[5][1] = y1;
	points[5][2] = x2 + 10;
	points[5][3] = y2 + 10;

	points[6][0] = x1;
	points[6][1] = y1;
	points[6][2] = x2 + 10;
	points[6][3] = y2 - 10;

	points[7][0] = x1;
	points[7][1] = y1;
	points[7][2] = x2 - 10;
	points[7][3] = y2 + 10;

	points[8][0] = x1;
	points[8][1] = y1;
	points[8][2] = x2 - 10;
	points[8][3] = y2 - 10;

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

	// calcul coef directeur pour provenance
}

void	client_broadcast(t_client *emitter)
{
	t_lstiter	iter;
	t_client	*receiver;

	init_iter(&iter, g_zappy.clients, increasing);
	while (lst_iterator_next(&iter))
	{
		receiver = iter.data;
		client_hear(receiver, emitter);
	}
}