/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_index_of.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 03:55:37 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 04:03:39 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"

size_t			lst_index_of(t_lst *l, void *data)
{
	t_lstiter	it;

	init_iter(&it, l, increasing);
	while (lst_iterator_next(&it))
	{
		if (it.data == data)
			return (it.pos);
	}
	return (LST_NOINDEX);
}
