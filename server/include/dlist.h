/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 02:42:36 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/30 18:31:27 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLIST_H
# define DLIST_H

# include <unistd.h>

# define DLIST_NOINDEX				((size_t)-1)
# define DLIST_FORWARD(TYPE, LIST)	LIST = (TYPE)((t_dlist*)LIST)->next;
# define DLIST_BACKWARD(TYPE, LIST)	LIST = (TYPE)((t_dlist*)LIST)->prev;
# define DLIST_NEXT(LIST)			((t_dlist*)LIST)->next
# define DLIST_PREV(LIST)			((t_dlist*)LIST)->prev
# define DLIST(FUNC, TYPE, TARGET, ...)	\
	(TYPE)dlist_ ## FUNC((t_dlist*)TARGET, ##__VA_ARGS__)

typedef struct						s_double_list
{
	struct s_double_list			*next;
	struct s_double_list			*prev;
}									t_double_list;

typedef struct s_double_list		t_dlist;

t_dlist								*dlist_create(size_t size);
void								dlist_append(t_dlist *node,
	t_dlist *new_node);
void								dlist_prepend(t_dlist *node,
	t_dlist *new_node);
t_dlist								*dlist_remove(t_dlist *node);
t_dlist								*dlist_shift(t_dlist *node);
t_dlist								*dlist_pop(t_dlist *node);
t_dlist								*dlist_first(t_dlist *node);
t_dlist								*dlist_last(t_dlist *node);
size_t								dlist_length(t_dlist *node);
size_t								dlist_index(t_dlist *node);
t_dlist								*dlist_at(t_dlist *node, size_t index);
void								dlist_swap(t_dlist *node1, t_dlist *node2);
void								dlist_replace(t_dlist *dest_node,
	t_dlist *src_node);
short								dlist_move_right(t_dlist *node);
short								dlist_move_left(t_dlist *node);

#endif