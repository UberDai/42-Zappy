/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 00:20:27 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/15 01:33:18 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>

#define OPTION_COUNT	6

typedef struct	s_option_fun
{
	char		*name;
	int			(*function)(t_uint, char **, t_uint);
}				t_option_fun;

static int	option_port(t_uint ac, char **av, t_uint i)
{
	i++;
	if (i >= ac)
		die("-p option need a value.");
	g_zappy.port = ft_atoi(av[i]);
	return (i + 1);
}

static int	option_width(t_uint ac, char **av, t_uint i)
{
	i++;
	if (i >= ac)
		die("-x option need a value.");
	g_zappy.width = ft_atoi(av[i]);
	return (i + 1);
}

static int	option_height(t_uint ac, char **av, t_uint i)
{
	i++;
	if (i >= ac)
		die("-y option need a value.");
	g_zappy.height = ft_atoi(av[i]);
	return (i + 1);
}

static int	option_teams(t_uint ac, char **av, t_uint i)
{
	i++;
	if (i >= ac)
		die("-n option need a value.");
	(void)av;
	return (i + 1);
}

static int	option_clients(t_uint ac, char **av, t_uint i)
{
	i++;
	if (i >= ac)
		die("-c option need a value.");
	g_zappy.client_count = ft_atoi(av[i]);
	return (i + 1);
}

static int	option_time(t_uint ac, char **av, t_uint i)
{
	i++;
	if (i >= ac)
		die("-t option need a value.");
	g_zappy.clock = ft_atoi(av[i]);
	return (i + 1);
}

t_option_fun	g_options[OPTION_COUNT] = {
	{ "-p", option_port },
	{ "-x", option_width },
	{ "-y", option_height },
	{ "-n", option_teams },
	{ "-c", option_clients },
	{ "-t", option_time }
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
}