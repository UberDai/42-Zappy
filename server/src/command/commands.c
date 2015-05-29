/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/21 01:02:58 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/29 16:59:03 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>

short	command_move(t_client *client, t_uint argc, char **argv)
{
	if (argc != 1)
		return (0);
	(void)client;
	(void)argc;
	(void)argv;
	return (1);
}

short	command_left(t_client *client, t_uint argc, char **argv)
{
	if (argc != 1)
		return (0);
	(void)client;
	(void)argc;
	(void)argv;
	return (1);
}

short	command_right(t_client *client, t_uint argc, char **argv)
{
	if (argc != 1)
		return (0);
	(void)client;
	(void)argc;
	(void)argv;
	return (1);
}

short	command_pause(t_client *client, t_uint argc, char **argv)
{
	if (client->gfx == 0)
		return (0);
	zappy_pause();
	(void)argc;
	(void)argv;
	return (1);
}

short	command_resume(t_client *client, t_uint argc, char **argv)
{
	if (client->gfx == 0)
		return (0);
	zappy_resume();
	(void)argc;
	(void)argv;
	return (1);
}