/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_swap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 23:33:07 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/22 23:38:13 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

void	dlist_swap(t_dlist *node1, t_dlist *node2)
{
	t_dlist	*prev1;
	t_dlist	*next1;
	t_dlist	*prev2;
	t_dlist	*next2;

	if (node1 == node2)
		return ;

	prev1 = node1->prev;
	next1 = node1->next;
	prev2 = node2->prev;
	next2 = node2->next;

	node1->prev = prev2;
	node1->next = next2;
	node2->prev = prev1;
	node2->next = next1;
}