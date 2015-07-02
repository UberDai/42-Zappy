/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 00:03:39 by amaurer           #+#    #+#             */
/*   Updated: 2015/06/14 04:55:47 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

// t_lst	*get_vision(t_client *client)
// {
// 	t_lst	*list;
// 	t_uint	row;
// 	int		col;
// 	int		x;
// 	int		y;

// 	list = new_lst();
// 	row = 0;
// 	while (row < (client->level + 1) + 1)
// 	{
// 		col = -(client->level + 1);

// 		while (col < client->level + 1)
// 		{
// 			col++;
// 		}

// 		printf("\n");
// 		row++;
// 	}

// 	return (list);
// }

/*


	0:0	1:0	2:0	3:0	4:0
	0:1	1:1	2:1	3:1	4:1
	0:2	1:2	2:2	3:2	4:2
	0:3	1:3	2:3	3:3	4:3
	0:4	1:4	2:4	3:4	4:4


*/

t_lst	*get_vision(t_client *client)
{
	t_lst	*list;
	t_uint	row;
	t_uint	col;
	int		x;
	int		y;

	list = new_lst();
	row = 0;
	while (row < (client->level + 1) + 1)
	{
		if (client->orientation == ORIENT_SOUTH || client->orientation == ORIENT_EAST)
			y = client->position->y + row;
		else if (client->orientation == ORIENT_NORTH || client->orientation == ORIENT_WEST)
			y = client->position->y - row;

		col = 0;
		while (col < row * 2 + 1)
		{
			if (client->orientation == ORIENT_NORTH || client->orientation == ORIENT_EAST)
				x = client->position->x + col - row;
			else if (client->orientation == ORIENT_SOUTH || client->orientation == ORIENT_WEST)
				x = client->position->x - col + row;
			if (row == 0 || client->orientation == ORIENT_NORTH || client->orientation == ORIENT_SOUTH)
			{
				printf("[%u;%u]\t", tile_at(x, y)->x, tile_at(x, y)->y);
				lst_push_back(list, tile_at(x, y));
			}
			else if (client->orientation == ORIENT_EAST)
			{
				y = -y;
				int xx = (y - client->position->y) * -1 + client->position->y;
				int yy = x;
				y = -y;
				yy = -yy;

				printf("[%u;%u]\t", tile_at(xx, yy)->x, tile_at(xx, yy)->y);
				lst_push_back(list, tile_at(xx, yy));
			}
			else if (client->orientation == ORIENT_WEST)
			{
				y = -y;
				int xx = y;
				int yy = (x - client->position->x) * -1 + client->position->x;
				y = -y;
				yy = -yy;

				printf("[%u;%u]\t", tile_at(xx, yy)->x, tile_at(xx, yy)->y);
				lst_push_back(list, tile_at(xx, yy));
			}
			col++;
		}
		printf("\n");
		row++;
	}

	return (list);
}
