/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 03:02:06 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/23 02:44:15 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"
#include <stdlib.h>
#include <libft.h>

t_dlist	*dlist_create(size_t size)
{
	t_dlist	*node;

	node = malloc(size);
	ft_bzero(node, size);
	return (node);
}