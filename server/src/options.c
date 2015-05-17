/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 00:20:27 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/16 23:46:38 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>
#include <stdlib.h>

#define OPTION_COUNT	7

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
	g_zappy.port = input;
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
	t_uint	j;

	i++;
	if (i >= ac)
		die("-n option need a value.");
	input = ft_atoi(av[i]);
	if (input < 0)
		die("-n must be a positive number followed by teams' names.");

	g_zappy.team_count = input;
	if (i + g_zappy.team_count >= ac)
		die("Bad team naming");

	g_zappy.teams = malloc(sizeof(char *) * g_zappy.team_count);
	i++;
	j = 0;

	while (i < ac && j < g_zappy.team_count)
	{
		g_zappy.teams[j] = ft_strdup(av[i]);
		i++;
		j++;
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
	g_zappy.client_count = input;
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

t_option_fun	g_options[OPTION_COUNT] = {
	{ "-h", option_help },
	{ "-p", option_port },
	{ "-x", option_width },
	{ "-y", option_height },
	{ "-n", option_teams },
	{ "-c", option_clients },
	{ "-t", option_time }
};

void	options_valid(void)
{
	if (g_zappy.time.cycle_duration == 0)
		die("-t must me equal or greater to 1.");
	else if (g_zappy.width == 0)
		die("-x must me equal or greater to 1.");
	else if (g_zappy.height == 0)
		die("-y must me equal or greater to 1.");
}

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
		while (j < OPTION_COUNT)
		{
			if (!ft_strcmp(g_options[j].name, av[i]))
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
}