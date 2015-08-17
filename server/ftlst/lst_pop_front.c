/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pop_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 03:56:04 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 03:56:28 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"
#include "ftlst_elem.h"

void					*lst_pop_front(t_lst *lst)
{
	t_lstelem			*first;

	if (lst->first == NULL)
		return (NULL);
	first = lst_elem_front(lst);
	if (first == lst_elem_back(lst))
		lst->first = NULL;
	else
		lst->first = first->next;
	--lst->size;
	return (elem_destroy(&first));
}
