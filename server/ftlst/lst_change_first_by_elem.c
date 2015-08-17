/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_change_first_by_elem.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/21 00:41:33 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/21 00:41:34 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"

void			lst_change_first_by_elem(t_lst *lst, t_lstelem *elem)
{
	if (elem)
		lst->first = elem;
}
