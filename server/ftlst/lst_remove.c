/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 03:56:15 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 03:56:28 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"
#include "ftlst_elem.h"

void					*lst_remove(t_lst *lst, size_t pos)
{
	t_lstelem			*cursor;

	if (pos >= lst_get_size(lst))
		return (0);
	cursor = lst_elem_at(lst, pos);
	if (pos == 0)
		lst->first = cursor->next;
	if (lst_elem_front(lst) == lst_elem_back(lst))
		lst->first = NULL;
	--lst->size;
	return (elem_destroy(&cursor));
}
