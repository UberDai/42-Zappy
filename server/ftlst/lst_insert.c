/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 03:55:59 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 03:56:28 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"
#include "ftlst_elem.h"

int						lst_insert(t_lst *lst, void *data, size_t pos)
{
	t_lstelem			*cursor;

	if (lst_is_empty(lst) || pos == 0)
		return (lst_push_front(lst, data));
	if (pos >= lst_get_size(lst))
		return (0);
	cursor = lst_elem_at(lst, pos);
	elem_insert_between(new_lstelem(data), cursor->prev, cursor);
	return (++lst->size);
}
