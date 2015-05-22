/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_shift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 02:53:43 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/22 03:00:15 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

t_dlist	*dlist_shift(t_dlist *node)
{
	while (node->prev)
		node = node->prev;
	if (node->next)
	{
		node->next->prev = NULL;
		node->next = NULL;
	}
	else
		return (NULL);
	return (node);
}