/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 03:07:29 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/22 03:09:39 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

void	dlist_append(t_dlist *node, t_dlist *new_node)
{
	if (node == new_node)
		return ;
	node = dlist_end(node);
	node->next = new_node;
	new_node->prev = node;
	new_node->next = NULL;
}