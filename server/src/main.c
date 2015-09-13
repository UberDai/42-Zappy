/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/14 22:43:52 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/13 22:31:24 by amaurer          ###   ########.fr       */
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

static void	init_zappy(void)
{
	g_item_names[0] = strdup("nourriture");
	g_item_names[1] = strdup("linemate");
	g_item_names[2] = strdup("deraumere");
	g_item_names[3] = strdup("sibur");
	g_item_names[4] = strdup("mendiane");
	g_item_names[5] = strdup("phiras");
	g_item_names[6] = strdup("thystame");
	bzero(&g_zappy, sizeof(t_zappy));
	g_zappy.clients = new_lst();
	g_zappy.anonymous_clients = new_lst();
	g_zappy.gfx_clients = new_lst();
	g_zappy.teams = new_lst();
	g_zappy.eggs = new_lst();
}

int			main(int ac, char **av)
{
	srand(time(NULL));
	init_zappy();
	logger_init("server_network.log");
	options_parse(ac, av);
	g_zappy.time.clock = 1.0 / (float)g_zappy.time.cycle_duration;
	map_init();
	signal_bind();
	zappy_run();
	logger_close();
	return (0);
}
