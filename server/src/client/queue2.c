/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/10 20:37:10 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 20:37:26 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>

void		client_queue_free(t_client *client)
{
	t_uint	i;

	i = 0;
	while (i < CLIENT_QUEUE_MAX)
	{
		client_queue_shift(client);
		i++;
	}
}
