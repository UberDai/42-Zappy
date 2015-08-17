/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 03:56:16 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 03:56:28 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"
#include "ftlst_elem.h"

void					lst_swap(t_lst *lst, size_t pos1, size_t pos2)
{
	t_lstelem			*cursor1;
	t_lstelem			*cursor2;

	if (pos1 >= lst_get_size(lst) || pos2 >= lst_get_size(lst) || pos1 == pos2)
		return ;
	cursor1 = lst_elem_at(lst, pos1);
	cursor2 = lst_elem_at(lst, pos2);
	elem_swap(cursor1, cursor2);
}
