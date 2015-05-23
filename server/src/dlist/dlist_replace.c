/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 23:39:34 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/22 23:42:37 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

void	dlist_replace(t_dlist *dest_node, t_dlist *src_node)
{
	src_node->prev = dest_node->prev;
	src_node->next = dest_node->next;
	if (src_node->next)
		src_node->next->prev = src_node;
	if (src_node->prev)
		src_node->prev->next = src_node;
	dest_node->prev = NULL;
	dest_node->next = NULL;
}