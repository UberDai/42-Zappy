/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 01:03:37 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/31 22:06:52 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>
#include <stdlib.h>
#include <sys/time.h>

double	get_time(void)
{
	static time_t	beginning;
	struct timeval	tod;
	double			ret;

	gettimeofday(&tod, NULL);
	if (beginning == 0)
		beginning = tod.tv_sec;
	ret = (double)(tod.tv_sec - beginning);
	ret += (double)tod.tv_usec / 1000000;
	return (ret);
}

int		die(const char *message)
{
	ft_putendl(message);
	exit(0);
	return (0);
}

void	print_client(t_client *client)
{
	if (client->status == STATUS_GFX)
		printf("#%u gfx\n", client->id);
	else
	{
		printf("#%u [%i;%i", client->id, client->position->x, client->position->y);
		if (client->orientation == ORIENT_NORTH)
			printf(";N]\n");
		else if (client->orientation == ORIENT_SOUTH)
			printf(";S]\n");
		else if (client->orientation == ORIENT_EAST)
			printf(";E]\n");
		else if (client->orientation == ORIENT_WEST)
			printf(";W]\n");
		else
			printf("]\n");
	}

}

void	print_client_queue(t_client *client)
{
	t_uint	i;

	printf("Queue #%u:\n", client->id);
	i = 0;
	while (i < CLIENT_QUEUE_MAX && client->queue[i].set)
	{
		printf("  [%u] %s (%u)\n", i, client->queue[i].av[0], client->queue[i].delay);
		i++;
	}
	printf("\n");
}

void	print_tile(t_tile *tile)
{
	printf("Tile [%i;%i]   F: %u, L: %u, D: %u, S: %u, M: %u, P: %u, T: %u\n",
		tile->x,
		tile->y,
		tile->items[0],
		tile->items[1],
		tile->items[2],
		tile->items[3],
		tile->items[4],
		tile->items[5],
		tile->items[6]
	);
}

int		rand_range(int min, int max)
{
	return ((rand() % max) + min);
}