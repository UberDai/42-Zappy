/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_elem_at.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 03:55:45 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 03:56:28 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"

static t_lstelem	*reg_search(t_lst *lst, size_t pos)
{
	t_lstelem		*cursor;
	size_t			i;

	cursor = lst_elem_front(lst);
	i = 0;
	while (i++ < pos)
		cursor = cursor->next;
	return (cursor);
}

static t_lstelem	*rev_search(t_lst *lst, size_t pos, size_t offset)
{
	t_lstelem		*cursor;

	cursor = lst_elem_back(lst);
	while (offset-- > pos)
		cursor = cursor->prev;
	return (cursor);
}

t_lstelem			*lst_elem_at(t_lst *lst, size_t pos)
{
	size_t			lsize;

	lsize = lst_get_size(lst);
	if (pos >= lsize)
		return (NULL);
	else if (pos == 0)
		return (lst_elem_front(lst));
	else if (pos == lsize - 1)
		return (lst_elem_back(lst));
	else if (pos <= (lsize / 2))
		return (reg_search(lst, pos));
	else
		return (rev_search(lst, pos, lsize - 1));
}
