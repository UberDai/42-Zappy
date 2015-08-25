/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_data_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 03:55:38 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 03:56:28 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"

void	*lst_data_back(t_lst *lst)
{
	return (lst_is_empty(lst) ? NULL : lst_elem_back(lst)->data);
}