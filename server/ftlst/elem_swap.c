/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 03:55:01 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 03:55:07 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"

void		elem_swap(t_lstelem *elem1, t_lstelem *elem2)
{
	void	*tmp;

	tmp = elem1->data;
	elem1->data = elem2->data;
	elem2->data = tmp;
}
