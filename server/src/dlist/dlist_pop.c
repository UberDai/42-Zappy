/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 02:53:43 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/22 03:00:48 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

t_dlist	*dlist_pop(t_dlist *node)
{
	while (node->next)
		node = node->next;
	if (node->prev)
	{
		node->prev->next = NULL;
		node->prev = NULL;
	}
	else
		return (NULL);
	return (node);
}