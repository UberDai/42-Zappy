/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 02:42:59 by amaurer           #+#    #+#             */
/*   Updated: 2015/08/19 00:53:40 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>

#define NETWORK_BUFFER_SIZE	1000

void		network_bind()
{
	struct sockaddr_in	server;
	int					option;

	if ((g_zappy.network.fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		die("Could not create the network socket.");

	option = 1;
	if (setsockopt(g_zappy.network.fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1)
		die("The port is still in use.");

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(g_zappy.network.port);

	if (bind(g_zappy.network.fd, (struct sockaddr *)&server, sizeof(server)) < 0)
		die("Could not bind the server to the network.");

	if (listen(g_zappy.network.fd, 10))
		die("Error: listen()");

	FD_ZERO(&g_zappy.network.read_fds);
	FD_ZERO(&g_zappy.network.write_fds);
	FD_SET(g_zappy.network.fd, &g_zappy.network.read_fds);
	FD_SET(g_zappy.network.fd, &g_zappy.network.write_fds);

	printf("Listening on port %u\n", g_zappy.network.port);
}

static void	network_client_connect(void)
{
	t_client			*client;
	struct sockaddr_in	sin;
	socklen_t			sin_size;

	sin_size = sizeof(struct sockaddr_in);
	bzero(&sin, sin_size);
	client = client_create();
	client->fd = accept(g_zappy.network.fd, (struct sockaddr *)&sin, &sin_size);

	if (client->fd == -1)
		die("Client connection error.");

	FD_SET(client->fd, &g_zappy.network.read_fds);
	FD_SET(client->fd, &g_zappy.network.write_fds);

	network_send(client, "BIENVENUE", 0);
	logger_client_connect(client);
}

void	network_client_disconnect(t_client *client)
{
	logger_client_disconnect(client);
	close(client->fd);
	FD_CLR(client->fd, &g_zappy.network.read_fds);
	FD_CLR(client->fd, &g_zappy.network.write_fds);
	if (client->status == STATUS_PLAYER)
		gfx_client_disconnect(client);
	client_delete(client);
}

static char	network_client_data(t_client *client, fd_set *read_fds)
{
	char		buffer[NETWORK_BUFFER_SIZE] = { 0 };
	char		*input;
	int			ret;

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
	size_t		size;
	char		*str;

	if (client->sending_queue->size == 0)
		return ;

	size = 0;
	init_iter(&iter, client->sending_queue, increasing);
	while (lst_iterator_next(&iter))
		size += strlen((char*)iter.data);

	str = calloc(size, sizeof(char));
	init_iter(&iter, client->sending_queue, increasing);
	while (lst_iterator_next(&iter))
		strcat(str, (char*)iter.data);
	send(client->fd, str, size, 0);
	free(str);

	lst_destroy(&client->sending_queue, free);
	client->sending_queue = new_lst();
	FD_CLR(client->fd, write_fds);
}

static void	network_check_clients(t_lst *clients, fd_set *read_fds, fd_set *write_fds)
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

static void	network_send_to_clients(t_client *emitter, t_lst *list, const char *str)
{
	t_lstiter	iter;
	t_client	*client;

	init_iter(&iter, list, increasing);
	while (lst_iterator_next(&iter))
	{
		client = (t_client*)iter.data;
		if (emitter == NULL || client != emitter)
			network_send(client, str, 0);
	}
}

void		network_send_team(const t_team *team, const char *str)
{
	t_lstiter	iter;
	t_client	*client;

	init_iter(&iter, g_zappy.clients, increasing);
	while (lst_iterator_next(&iter))
	{
		client = (t_client*)iter.data;
		if (client->team == team)
			network_send(client, str, 0);
	}
}

void		network_send(t_client *client, const char *str, int options)
{
	char		*output;

	if (options != 0)
	{
		if (options & (NET_SEND_CLIENT | NET_SEND_ALL))
			network_send_to_clients(client, g_zappy.clients, str);
		if (options & (NET_SEND_GFX | NET_SEND_ALL))
			network_send_to_clients(client, g_zappy.gfx_clients, str);
	}
	else
	{
		output = calloc(strlen(str) + 2, sizeof(char));
		strcat(output, str);
		strcat(output, "\n");
		logger_client_send(client, output);
		lst_push_back(client->sending_queue, output);
	}
}

void	network_disconnect(void)
{
	t_client	*client;

	printf("\n");

	while (g_zappy.clients->size > 0 && (client = lst_data_at(g_zappy.clients, 0)))
		network_client_disconnect(client);

	while (g_zappy.gfx_clients->size > 0 && (client = lst_data_at(g_zappy.gfx_clients, 0)))
		network_client_disconnect(client);

	FD_ZERO(&g_zappy.network.read_fds);
	FD_ZERO(&g_zappy.network.write_fds);
	close(g_zappy.network.fd);
	printf("Server disconnected.\n");
}
