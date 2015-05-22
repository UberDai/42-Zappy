/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_prepend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 03:07:29 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/22 03:10:10 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

void	dlist_prepend(t_dlist *node, t_dlist *new_node)
{
	if (node == new_node)
		return ;
	node = dlist_start(node);
	node->prev = new_node;
	new_node->next = node;
	new_node->prev = NULL;
}