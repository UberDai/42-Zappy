/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_data_at.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 03:55:37 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 04:03:39 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"

void			*lst_data_at(t_lst *lst, size_t pos)
{
	t_lstelem	*e;

	e = lst_elem_at(lst, pos);
	if (e)
		return (e->data);
	return (NULL);
}
