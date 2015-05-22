/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 02:46:42 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/22 02:57:23 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

size_t	dlist_length(t_dlist *node)
{
	size_t	i;

	i = 0;
	node = dlist_start(node);
	while (node)
	{
		node = node->next;
		i++;
	}
	return (i);
}