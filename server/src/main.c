/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/14 22:43:52 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/17 02:21:13 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void		usage(void)
{
	ft_putendl("Usage: ./serveur -p <port> -x <width> -y <height> -n <team>"
		"[<team>] [<team>] ... -c <nb> -t <t>");
	ft_putendl("  -p numero de port");
	ft_putendl("  -x largeur du Monde");
	ft_putendl("  -y hauteur du Monde");
	ft_putendl("  -n nombre_equipes nom_equipe_1 nom_equipe_2 ...");
	ft_putendl("  -c nombre de client autorises au commencement du jeu");
	ft_putendl("  -t diviseur de l'unite de temps (plus t est grand, plus le"
		"jeu va vite)");
}

static void	run_sleeping(void)
{
	static short	alert;
	static double	old_time;
	double			current_time;
	double			sleeping_duration;

	current_time = get_time();
	if (old_time == 0)
		sleeping_duration = g_zappy.time.clock;
	else
		sleeping_duration = g_zappy.time.clock - (current_time - old_time);
	if (sleeping_duration > 0)
		usleep(sleeping_duration * 1000000);
	else if (!alert)
	{
		alert = 1;
		ft_putendl("Warning: the clock is too fast ; the game may lag.");
	}
	old_time = get_time();
}

static void	run(void)
{
	while (1)
	{
		printf("[ Cycle %u ]\n", g_zappy.time.cycle_count);
		run_sleeping();
		g_zappy.time.cycle_count++;
	}
}

int		main(int ac, char **av)
{
	bzero(&g_zappy, sizeof(t_zappy));
	options_parse(ac, av);
	g_zappy.time.clock = 1.0 / (float)g_zappy.time.cycle_duration;
	map_init();
	client_create(tile_at(1, 1));
	(void)run;
	run();
	return (0);
}