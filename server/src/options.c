/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 00:20:27 by amaurer           #+#    #+#             */
/*   Updated: 2015/08/15 01:27:26 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>
#include <stdlib.h>

typedef struct	s_option_fun
{
	char		*name;
	int			(*function)(t_uint, char **, t_uint);
}				t_option_fun;

static int	option_help(t_uint ac, char **av, t_uint i)
{
	(void)ac;
	(void)av;
	(void)i;
	usage();
	exit(0);
	return (0);
}

static int	option_port(t_uint ac, char **av, t_uint i)
{
	int	input;

	i++;
	if (i >= ac)
		die("-p option need a value.");
	input = ft_atoi(av[i]);
	if (input < 0)
		die("-p must be a positive number.");
	g_zappy.network.port = input;
	return (i + 1);
}

static int	option_width(t_uint ac, char **av, t_uint i)
{
	int	input;

	i++;
	if (i >= ac)
		die("-x option need a value.");
	input = ft_atoi(av[i]);
	if (input < 0)
		die("-x must be a positive number.");
	g_zappy.width = input;
	return (i + 1);
}

static int	option_height(t_uint ac, char **av, t_uint i)
{
	int	input;

	i++;
	if (i >= ac)
		die("-y option need a value.");
	input = ft_atoi(av[i]);
	if (input < 0)
		die("-y must be a positive number.");
	g_zappy.height = input;
	return (i + 1);
}

static int	option_teams(t_uint ac, char **av, t_uint i)
{
	int		input;

	i++;
	if (i >= ac)
		die("-n option need a value.");
	input = ft_atoi(av[i]);
	if (input < 0)
		die("-n must be a positive number followed by teams' names.");

	if (i + input >= ac)
		die("Bad team naming");

	i++;
	while (i < ac && input > 0)
	{
		team_create(av[i]);
		i++;
		input--;
	}

	return (i);
}

static int	option_clients(t_uint ac, char **av, t_uint i)
{
	int	input;

	i++;
	if (i >= ac)
		die("-c option need a value.");
	input = ft_atoi(av[i]);
	if (input < 0)
		die("-c must be a positive number.");
	g_zappy.max_clients = input;
	return (i + 1);
}

static int	option_time(t_uint ac, char **av, t_uint i)
{
	int	input;

	i++;
	if (i >= ac)
		die("-t option need a value.");
	input = ft_atoi(av[i]);
	if (input < 0)
		die("-t must be a positive number.");
	g_zappy.time.cycle_duration = input;
	return (i + 1);
}

void	options_valid(void)
{
	if (g_zappy.time.cycle_duration == 0)
		die("-t must me equal or greater to 1.");
	else if (g_zappy.width == 0)
		die("-x must me equal or greater to 1.");
	else if (g_zappy.height == 0)
		die("-y must me equal or greater to 1.");
	else if (g_zappy.max_clients == 0)
		die("-c must me equal or greater to 1.");
}

static void	set_team_max_clients(void)
{
	t_team		*team;
	t_lstiter	iter;

	init_iter(&iter, g_zappy.teams, increasing);
	while (lst_iterator_next(&iter))
	{
		team = (t_team*)iter.data;
		team->max_clients = g_zappy.max_clients;
	}
}

t_option_fun	g_options[] = {
	{ "-h", option_help },
	{ "-p", option_port },
	{ "-x", option_width },
	{ "-y", option_height },
	{ "-n", option_teams },
	{ "-c", option_clients },
	{ "-t", option_time },
	{ NULL, NULL }
};

void	options_parse(t_uint ac, char **av)
{
	short	option_exists;
	t_uint	i;
	t_uint	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		option_exists = 0;
		while (g_options[j].name)
		{
			if (!strcmp(g_options[j].name, av[i]))
			{
				option_exists = 1;
				i = g_options[j].function(ac, av, i);
				break ;
			}
			j++;
		}
		if (!option_exists)
			die("Unknown option");
	}
	options_valid();
	set_team_max_clients();
}
