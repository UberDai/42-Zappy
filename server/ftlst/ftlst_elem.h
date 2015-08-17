/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftlst_elem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 05:50:49 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 05:50:50 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTLST_ELEM_H
# define FTLST_ELEM_H

# include "ftlst.h"

typedef void	*t_supernorm;
/*
** Creates a new list elem. Sets all pointers to NULL.
*/
t_lstelem		*new_lstelem(void *data);
/*
** Inserts to_insert between before and after, editing pointers
** accordingly.
*/
void			elem_insert_between(
					t_lstelem *to_insert,
					t_lstelem *before,
					t_lstelem *after);
/*
** Swaps data of elem1 and elem2.
*/
void			elem_swap(t_lstelem *elem1, t_lstelem *elem2);
/*
** Destroys elem, setting pointers to it's neighbours elements correctly.
*/
void			*elem_destroy(t_lstelem **elem);

#endif
