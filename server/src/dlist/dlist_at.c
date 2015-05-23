/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/23 00:29:56 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/23 00:32:44 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

t_dlist	*dlist_at(t_dlist *node, size_t index)
{
	node = dlist_first(node);
	while (node && index-- > 0)
		node = node->next;
	if (index == 0)
		return (node);
	return (NULL);
}