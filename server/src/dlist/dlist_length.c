/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 02:46:42 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/23 00:33:36 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

size_t	dlist_length(t_dlist *node)
{
	size_t	i;

	i = 0;
	node = dlist_first(node);
	while (node)
	{
		node = node->next;
		i++;
	}
	return (i);
}