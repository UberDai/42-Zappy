/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 22:00:27 by amaurer           #+#    #+#             */
/*   Updated: 2015/06/03 00:10:17 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

short	client_eat(t_client *client)
{
	if (client->items[ITEM_FOOD] == 0)
		return (0);
	client->items[ITEM_FOOD]--;
	client->hunger = FOOD_DURATION;
	return (1);
}