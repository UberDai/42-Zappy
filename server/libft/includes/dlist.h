/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 02:42:36 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/22 03:15:57 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLIST_H
# define DLIST_H

# include <unistd.h>

# define DLIST_NOINDEX			((size_t)-1)

typedef struct					s_double_list
{
	struct s_double_list		*next;
	struct s_double_list		*prev;
}								t_double_list;

typedef struct s_double_list	t_dlist;

t_dlist							*dlist_create(size_t size);
void							dlist_append(t_dlist *node, t_dlist *new_node);
void							dlist_prepend(t_dlist *node, t_dlist *new_node);
t_dlist							*dlist_remove(t_dlist *node);
t_dlist							*dlist_shift(t_dlist *node);
t_dlist							*dlist_pop(t_dlist *node);
t_dlist							*dlist_start(t_dlist *node);
t_dlist							*dlist_end(t_dlist *node);
size_t							dlist_length(t_dlist *node);
size_t							dlist_index(t_dlist *node);

#endif