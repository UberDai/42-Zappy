/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 02:05:55 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 20:08:38 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>
#include <libft.h>
#include <string.h>

t_team	*team_get(const char *name)
{
	t_team		*team;
	t_lstiter	iter;

	init_iter(&iter, g_zappy.teams, increasing);
	while (lst_iterator_next(&iter))
	{
		team = (t_team*)iter.data;
		if (strcmp(team->name, name) == 0)
			return (team);
	}
	return (NULL);
}

t_team	*team_create(const char *team_name)
{
	t_team	*team;

	team = calloc(1, sizeof(t_team*));
	team->name = ft_strsub(team_name, 0, 20);
	lst_push_back(g_zappy.teams, team);
	return (team);
}

size_t	team_count_clients(t_team *team)
{
	t_client	*client;
	t_lstiter	iter;
	size_t		i;

	i = 0;
	init_iter(&iter, g_zappy.clients, increasing);
	while (lst_iterator_next(&iter))
	{
		client = (t_client*)iter.data;
		if (client->team == team)
			i++;
	}
	return (i);
}
