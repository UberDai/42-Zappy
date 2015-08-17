/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   egg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/15 00:20:50 by amaurer           #+#    #+#             */
/*   Updated: 2015/08/16 00:00:23 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>

t_egg	*egg_create(const t_client *client)
{
	t_egg	*egg;

	egg = calloc(1, sizeof(t_egg));
	egg->team = client->team;
	egg->position = client->position;
	egg->hatch_time = g_zappy.time.cycle_count + EGG_MATURATION;
	lst_push_back(g_zappy.eggs, egg);
	gfx_egg_add(egg);
	return (egg);
}

void	egg_remove(t_egg *egg)
{
	lst_remove(g_zappy.eggs, lst_index_of(g_zappy.eggs, egg));
	gfx_egg_remove(egg);
	free(egg);
}

void	egg_hatch(t_egg *egg)
{
	egg->team->max_clients++;
	egg->has_hatched = 1;
}

t_egg	*get_hatched_egg(const t_team *team)
{
	t_lstiter	iter;
	t_egg		*egg;

	init_iter(&iter, g_zappy.eggs, increasing);
	while (lst_iterator_next(&iter))
	{
		egg = (t_egg*)iter.data;
		if (egg->team == team && egg->has_hatched)
			return (egg);
	}
	return (NULL);
}

void	watch_eggs(void)
{
	t_lstiter	iter;
	t_egg		*egg;

	init_iter(&iter, g_zappy.eggs, increasing);
	while (lst_iterator_next(&iter))
	{
		egg = (t_egg*)iter.data;
		if (egg->hatch_time == g_zappy.time.cycle_count)
			egg_hatch(egg);
	}
}
