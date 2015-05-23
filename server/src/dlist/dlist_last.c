/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 02:44:58 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/23 02:45:47 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"
#include <stdio.h>

t_dlist	*dlist_last(t_dlist *node)
{
	while (node->next != NULL)
		node = node->next;
	return (node);
}