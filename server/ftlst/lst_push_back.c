/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_push_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 03:56:11 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 03:56:28 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"
#include "ftlst_elem.h"

int						lst_push_back(t_lst *lst, void *data)
{
	t_lstelem			*new_elem;

	if (!(new_elem = new_lstelem(data)))
		return (0);
	else if (lst_is_empty(lst))
	{
		new_elem->prev = new_elem;
		new_elem->next = new_elem;
		lst->first = new_elem;
		return (++lst->size);
	}
	elem_insert_between(new_elem, lst_elem_back(lst), lst_elem_front(lst));
	return (++lst->size);
}
