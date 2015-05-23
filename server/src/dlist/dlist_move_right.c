/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_move_right.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 23:45:09 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/23 00:42:58 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

short	dlist_move_right(t_dlist *node)
{
	if (node->next == NULL)
		return (0);
	dlist_swap(node, node->next);
	return (1);
}