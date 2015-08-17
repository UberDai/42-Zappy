/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftlst.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 04:25:01 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 04:25:02 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTLST_H
# define FTLST_H
# define LST_NOINDEX ((size_t)-1)
# include <stddef.h>

typedef enum			e_lst_direction
{
	increasing,
	decreasing,
	end
}						t_lst_direction;

typedef struct			s_lstelem
{
	void				*data;
	struct s_lstelem	*prev;
	struct s_lstelem	*next;
}						t_lstelem;

typedef struct			s_lstiter
{
	void				*data;
	t_lstelem			*current;
	size_t				pos;
	t_lstelem			*end;
	t_lst_direction		dir;
	int					flag;

}						t_lstiter;

typedef struct			s_lst
{
	size_t				size;
	t_lstelem			*first;
}						t_lst;
/*
** Creates an empty list.
*/
t_lst					*new_lst(void);
/*
** Returns actual size of list.
*/
size_t					lst_get_size(t_lst *lst);
/*
** Returns 1 if empty, 0 if not.
*/
int						lst_is_empty(t_lst *lst);
/*
** Returns the index of given data, or LST_NOINDEX if not found
*/
size_t					lst_index_of(t_lst *l, void *data);
/*
** Returns a pointer to the list element at pos if pos is valid. Otherwise,
** returns NULL.
*/
t_lstelem				*lst_elem_at(t_lst *lst, size_t pos);
/*
** Returns a pointer to the data at pos if pos is valid. Otherwise,
** returns NULL.
*/
void					*lst_data_at(t_lst *lst, size_t pos);
/*
** Returns first element or NULL if list is empty.
*/
t_lstelem				*lst_elem_front(t_lst *lst);
/*
** Returns last element or NULL if list is empty.
*/
t_lstelem				*lst_elem_back(t_lst *lst);
/*
** Returns first data or NULL if list is empty.
*/
void					*lst_data_front(t_lst *lst);
/*
** Returns last data or NULL if list is empty.
*/
void					*lst_data_back(t_lst *lst);
/*
** Adds data at the end of the list. Returns new list size if successful,
** otherwise 0.
*/
int						lst_push_back(t_lst *lst, void *data);
/*
** Adds data at the beggining of the list. Returns the new list size if
** successful, otherwise 0.
*/
int						lst_push_front(t_lst *lst, void *data);
/*
** Deletes last element and returns a pointer to its data (in case you must
** free it).
*/
void					*lst_pop_back(t_lst *lst);
/*
** Deletes first element and returns a pointer to its data (in case you must
** free it).
*/
void					*lst_pop_front(t_lst *lst);
/*
** Inserts data in position pos, if pos is valid. New list size on success,
** 0 otherwise.
*/
int						lst_insert(t_lst *lst, void *data, size_t pos);
/*
** Changes the head of the list given a position. If position is invalid,
** the function does nothing.
*/
void					lst_change_first_by_pos(t_lst *lst, size_t pos);
/*
** Changes the head of the list given an element.
*/
void					lst_change_first_by_elem(t_lst *lst, t_lstelem *elem);
/*
** Deletes element at pos if pos is valid and returns a pointer to the data
** (in case you must free it).
*/
void					*lst_remove(t_lst *lst, size_t pos);
/*
** Swaps data of elements at pos1 and pos2 if both are valid.
*/
void					lst_swap(t_lst *lst, size_t pos1, size_t pos2);
/*
** Apply an increasing bubble sort to the list, using function f as comparison.
*/
void					lst_bubble_sort(t_lst *lst, int (*f)(void *, void *));
/*
** Prints list using print_f to print data. Last argument is the print mode.
** 0 is simple (only data is printed), 1 is for debug (meta-data also printed).
*/
void					lst_print(t_lst *lst, void (*print_f)(void *), int m);
/*
** Clears the whole list (frees all elements but no data).
*/
void					lst_clear(t_lst *lst);
/*
** Frees all elements, all data using f, the list in itself and sets
** its pointer to NULL. Pass NULL as f if you do not want to free the data.
*/
void					lst_destroy(t_lst **lst, void (*f)(void *));
/*
** Creates an interator for a list, considering a direction.
*/
t_lstiter				*new_lstiter(t_lst *lst, t_lst_direction dir);
void					init_iter(t_lstiter *it, t_lst *l, t_lst_direction d);
/*
** Used to iterate through list considering the iterator position.
** Returns 0 if iteration is over, 1 othewise.
*/
int						lst_iterator_next(t_lstiter *it);

#endif
