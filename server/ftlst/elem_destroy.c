/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 03:54:38 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 03:54:42 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"
#include <stdlib.h>

void			*elem_destroy(t_lstelem **elem)
{
	t_lstelem	*elem_;
	t_lstelem	*left;
	t_lstelem	*right;
	void		*ret;

	elem_ = *elem;
	if (!(elem_->next == elem_))
	{
		left = elem_->prev;
		right = elem_->next;
		left->next = right;
		right->prev = left;
	}
	ret = elem_->data;
	free(elem_);
	*elem = NULL;
	return (ret);
}
