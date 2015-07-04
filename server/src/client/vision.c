/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 00:03:39 by amaurer           #+#    #+#             */
/*   Updated: 2015/07/04 16:34:04 by amaurer          ###   ########.fr       */
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

t_lst	*get_vision(t_client *client)
{
	(void)rotate_90;
	(void)rotate_180;
	(void)rotate_270;

	t_lst	*list;
	int		row;
	int		col;
	int		x;
	int		y;

	client->level = 1;

	list = new_lst();
	row = 0;
	while (row <= LEVEL)
	{
		col = -row;

		while (col <= row)
		{
			x = col;
			y = row;
			rotate_90(&x, &y);
			printf("%i %i\t", x, y);
			col++;
		}
		printf("\n");
		row++;
	}

	printf("\n");

	return (list);
}
