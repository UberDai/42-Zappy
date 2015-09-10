/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/10 19:47:09 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 19:47:59 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>
#include <stdlib.h>

int	option_help(t_uint ac, char **av, t_uint i)
{
	(void)ac;
	(void)av;
	(void)i;
	usage();
	exit(0);
	return (0);
}

int	option_port(t_uint ac, char **av, t_uint i)
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

int	option_width(t_uint ac, char **av, t_uint i)
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

int	option_height(t_uint ac, char **av, t_uint i)
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

int	option_teams(t_uint ac, char **av, t_uint i)
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
