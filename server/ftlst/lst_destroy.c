/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 03:55:44 by nsierra-          #+#    #+#             */
/*   Updated: 2015/08/19 01:12:42 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"
#include <stdlib.h>

void					lst_destroy(t_lst **lst, void (*f)(void *))
{
	void				*data;
	t_lst				*list;

	list = *lst;
	while ((data = lst_pop_back(list)))
	{
		if (f)
			f(data);
	}
	free(list);
	*lst = NULL;
}
