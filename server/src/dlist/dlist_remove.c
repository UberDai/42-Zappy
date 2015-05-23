/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 03:10:24 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/23 00:33:44 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

t_dlist	*dlist_remove(t_dlist *node)
{
	t_dlist	*next;
	t_dlist	*prev;

	next = node->next;
	prev = node->prev;

	if (next)
		next->prev = prev;
	if (prev)
		prev->next = next;

	if (next)
		return (dlist_first(next));
	else if (prev)
		return (dlist_first(prev));
	return (NULL);
}