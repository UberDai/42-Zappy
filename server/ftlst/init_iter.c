/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_iter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 09:11:27 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 09:11:35 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"
#include <stdlib.h>
#include <stdint.h>

void	init_iter(t_lstiter *it, t_lst *l, t_lst_direction d)
{
	it->pos = d == increasing ? SIZE_MAX : lst_get_size(l);
	it->current = d == increasing ? lst_elem_back(l) : lst_elem_front(l);
	it->end = d == increasing ? lst_elem_front(l) : lst_elem_back(l);
	it->dir = d;
	it->flag = 0;
}
