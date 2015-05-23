/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 02:05:55 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/23 03:13:25 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include "dlist.h"
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
		DLIST_FORWARD(t_team*, team);
	}
	return (NULL);
}

t_team	*team_create(const char *team_name)
{
	t_team	*team;

	team = (t_team*)dlist_create(sizeof(t_team));
	team->name = ft_strdup(team_name);

	if (g_zappy.teams == NULL)
		g_zappy.teams = team;
	else
		DLIST(append, void, g_zappy.teams, (t_dlist*)team);

	g_zappy.team_count++;

	return (team);
}