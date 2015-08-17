/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lstiter.c                                      :+:      :+:    :+:   */
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

t_lstiter		*new_lstiter(t_lst *l, t_lst_direction d)
{
	t_lstiter	*new_it;

	if (!(new_it = malloc(sizeof(t_lstiter))))
		return (NULL);
	init_iter(new_it, l, d);
	return (new_it);
}
