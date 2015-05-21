/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/21 00:33:28 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/21 03:16:09 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>

t_command	g_commands[] = {
	{ "move", 7, command_move },
	{ "left", 7, command_left },
	{ "right", 7, command_right },
	{ NULL, 0, NULL }
};

void	command_parse(t_client *client, char *input)
{
	char	**splits;
	t_uint	split_count;
	t_uint	i;

	splits = ft_strsplit(input, ' ');
	split_count = ft_splits_count(splits);

	i = 0;
	while (g_commands[i].name != NULL)
	{
		if (ft_strcmp(g_commands[i].name, splits[0]) == 0)
		{
			if (!client_queue_push(client, splits, g_commands[i].delay))
			{
				// TODO: queue is full
			}
			print_client_queue(client);
			return ;
		}
		i++;
	}

	// TODO: bad command
}