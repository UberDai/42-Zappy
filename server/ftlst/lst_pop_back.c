/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pop_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 03:56:02 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 03:56:28 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"
#include "ftlst_elem.h"

void					*lst_pop_back(t_lst *lst)
{
	t_lstelem			*last;

	if (lst->first == NULL)
		return (NULL);
	last = lst_elem_back(lst);
	if (last == lst_elem_front(lst))
		lst->first = NULL;
	--lst->size;
	return (elem_destroy(&last));
}
