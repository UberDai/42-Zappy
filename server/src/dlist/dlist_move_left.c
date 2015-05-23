/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_move_left.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 23:45:09 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/23 00:43:04 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

short	dlist_move_left(t_dlist *node)
{
	if (node->prev == NULL)
		return (0);
	dlist_swap(node, node->prev);
	return (1);
}