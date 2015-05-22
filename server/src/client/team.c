/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 02:05:55 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/22 02:24:31 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>
#include <libft.h>

t_team	*team_get(const char *name)
{
	t_team	*team;

	team = g_zappy.teams;
	while (team)
	{
		if (ft_strcmp(team->name, name) == 0)
			return (team);
		team = team->next;
	}
	return (NULL);
}

t_team	*team_create(const char *team_name)
{
	t_team	*team;
	t_team	*iter;

	team = malloc(sizeof(t_team));
	ft_bzero(team, sizeof(t_team));
	team->name = ft_strdup(team_name);

	iter = g_zappy.teams;
	if (iter == NULL)
		g_zappy.teams = team;
	else
	{
		while (iter->next)
			iter = iter->next;
		iter->next = team;
	}

	g_zappy.team_count++;

	return (team);
}