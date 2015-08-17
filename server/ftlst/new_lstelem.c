/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lstelem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 03:56:18 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 03:56:28 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"
#include <stdlib.h>

t_lstelem		*new_lstelem(void *data)
{
	t_lstelem	*new_elem;

	if (!(new_elem = malloc(sizeof(t_lstelem))))
		return (NULL);
	new_elem->data = data;
	new_elem->next = NULL;
	new_elem->prev = NULL;
	return (new_elem);
}
