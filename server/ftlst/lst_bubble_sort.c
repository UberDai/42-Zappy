/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_bubble_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 03:55:09 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 04:02:56 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"
#include "ftlst_elem.h"

void					lst_bubble_sort(t_lst *lst, int (*cmp)(void *, void *))
{
	int					sorted;
	t_lstelem			*cursor;

	sorted = 0;
	if (lst_get_size(lst) == 1)
		return ;
	while (!sorted)
	{
		cursor = lst_elem_front(lst);
		sorted = 1;
		while (42)
		{
			if (cursor->next == lst_elem_front(lst))
				break ;
			if (cmp(cursor->data, cursor->next->data) > 0)
			{
				elem_swap(cursor, cursor->next);
				sorted = 0;
			}
			cursor = cursor->next;
		}
	}
}
