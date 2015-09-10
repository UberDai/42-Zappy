/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_receive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/10 21:09:24 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 21:11:41 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <libft.h>
#include <sys/socket.h>

#define NETWORK_BUFFER_SIZE	1000

static char	network_client_data(t_client *client, fd_set *read_fds)
{
	char		buffer[NETWORK_BUFFER_SIZE];
	char		*input;
	int			ret;

	bzero(buffer, NETWORK_BUFFER_SIZE);
	ret = read(client->fd, buffer, NETWORK_BUFFER_SIZE - 1);
	FD_CLR(client->fd, read_fds);
	if (ret == -1)
		die("Could not read the client.");
	else if (ret == 0)
	{
		network_client_disconnect(client);
		return (0);
	}
	else
	{
		input = ft_strsub(buffer, 0, strlen(buffer) - 1);
		logger_client_receive(client, input);
		ret = command_parse(client, input);
		free(input);
		return (ret);
	}
	return (0);
}

static void	network_send_client_queue(t_client *client, fd_set *write_fds)
{
	t_lstiter	iter;
	char		*str;
	char		*tmp;

	if (client->sending_queue->size == 0)
		return ;
	str = NULL;
	init_iter(&iter, client->sending_queue, increasing);
	while (lst_iterator_next(&iter))
	{
		if (str == NULL)
			str = strdup((char*)iter.data);
		else
		{
			tmp = str;
			asprintf(&str, "%s%s", str, (char*)iter.data);
			if (tmp)
				free(tmp);
		}
	}
	send(client->fd, str, strlen(str), 0);
	free(str);
	lst_destroy(&client->sending_queue, free);
	client->sending_queue = new_lst();
	FD_CLR(client->fd, write_fds);
}

static void	network_check_clients(t_lst *clients, fd_set *read_fds,
	fd_set *write_fds)
{
	t_client	*client;
	size_t		i;

	i = 0;
	while (i < clients->size)
	{
		client = lst_data_at(clients, i);
		if (FD_ISSET(client->fd, read_fds))
		{
			if (network_client_data(client, read_fds) == 0)
				continue;
		}
		if (FD_ISSET(client->fd, write_fds) && client->sending_queue->size != 0)
			network_send_client_queue(client, write_fds);
		i++;
	}
}

static void	network_select(double remaining_time)
{
	static struct timeval	timeout;
	fd_set					read_fds;
	fd_set					write_fds;

	read_fds = g_zappy.network.read_fds;
	write_fds = g_zappy.network.write_fds;
	timeout.tv_sec = 0;
	timeout.tv_usec = remaining_time * 1000000;
	if (select(FD_SETSIZE, &read_fds, &write_fds, NULL, &timeout) < 0)
		die("Error: select()");
	if (FD_ISSET(g_zappy.network.fd, &read_fds))
		network_client_connect();
	else
	{
		network_check_clients(g_zappy.anonymous_clients, &read_fds, &write_fds);
		network_check_clients(g_zappy.gfx_clients, &read_fds, &write_fds);
		network_check_clients(g_zappy.clients, &read_fds, &write_fds);
	}
}

void		network_receive(void)
{
	double	timeout;

	while (1)
	{
		timeout = g_zappy.time.next_cycle - get_time();
		if (timeout <= 0)
			break ;
		network_select(timeout);
	}
}
