/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 02:42:59 by amaurer           #+#    #+#             */
/*   Updated: 2015/06/02 00:07:35 by amaurer          ###   ########.fr       */
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

#define NETWORK_BUFFER_SIZE	500

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

	if (bind(g_zappy.network.fd, (struct sockaddr *) &server, sizeof(server)) < 0)
		die("Could not bind the server to the network.");

	if (listen(g_zappy.network.fd, 10))
		die("Error: listen()");

	FD_ZERO(&(g_zappy.network.read_fds));
	FD_SET(g_zappy.network.fd, &(g_zappy.network.read_fds));

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

	FD_SET(client->fd, &(g_zappy.network.read_fds));
	printf("Client #%u created.\n", client->id);

	network_send(client, "BIENVENUE", 0);
}

t_client *	network_client_disconnect(t_client *client)
{
	t_client	*prev_client;

	prev_client = (t_client*)DLIST_NEXT(client);
	network_send(client, "GTFO", 0);
	printf("Client #%u disconnected.\n", client->id);
	close(client->fd);
	FD_CLR(client->fd, &(g_zappy.network.read_fds));
	if (client->status == STATUS_PLAYER)
		gfx_client_disconnect(client);
	client_delete(client);
	return (prev_client);
}

static t_client *	network_client_data(t_client *client, fd_set *fds)
{
	char		buffer[NETWORK_BUFFER_SIZE] = { 0 };
	char		*input;
	int			ret;

	ret = read(client->fd, buffer, NETWORK_BUFFER_SIZE - 1);
	FD_CLR(client->fd, fds);

	if (ret == -1)
		die("Could not read the client.");
	else if (ret == 0)
		return network_client_disconnect(client);
	else
	{
		input = ft_strsub(buffer, 0, strlen(buffer) - 1);
		client = command_parse(client, input);
		free(input);
	}
	return (client);
}

static void	network_check_clients(fd_set *read_fds, t_client *clients, fd_set *fds)
{
	while (clients)
	{
		if (FD_ISSET(clients->fd, read_fds))
			clients = network_client_data(clients, fds);
		if (clients != NULL)
			DLIST_FORWARD(t_client*, clients);
	}
}

static void	network_select(double remaining_time)
{
	static struct timeval	timeout;
	fd_set					read_fds;

	read_fds = g_zappy.network.read_fds;

	timeout.tv_sec = 0;
	timeout.tv_usec = remaining_time * 1000000;

	if (select(FD_SETSIZE, &read_fds, NULL, NULL, &timeout) < 0)
		die("Error: select()");

	if (FD_ISSET(g_zappy.network.fd, &read_fds))
		network_client_connect();
	else
	{
		network_check_clients(&read_fds, g_zappy.anonymous_clients, &read_fds);
		network_check_clients(&read_fds, g_zappy.gfx_clients, &read_fds);
		network_check_clients(&read_fds, g_zappy.clients, &read_fds);
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

static void	network_send_to_client(t_client *emitter, t_client *clients, char *str)
{
	while (clients)
	{
		if (emitter == NULL || clients != emitter)
			send(clients->fd, str, strlen(str), 0);
		clients = clients->next;
	}
}

void		network_send(t_client *client, char *str, int options)
{
	char		*output;

	output = ft_strnew(strlen(str) + 1);
	strcat(output, str);
	strcat(output, "\n");
	if (options != 0)
	{
		if (options & (NET_SEND_CLIENT | NET_SEND_ALL))
			network_send_to_client(client, g_zappy.clients, output);
		if (options & (NET_SEND_GFX | NET_SEND_ALL))
			network_send_to_client(client, g_zappy.gfx_clients, output);
	}
	else
		send(client->fd, output, strlen(output), 0);
	free(output);
}

void	network_disconnect(void)
{
	t_client	*client;

	printf("\n");
	client = g_zappy.clients;
	while (client)
	{
		client = network_client_disconnect(client);
		if (client != NULL)
			client = client->next;
	}
	client = g_zappy.gfx_clients;
	while (client)
	{
		client = network_client_disconnect(client);
		if (client != NULL)
			DLIST_FORWARD(t_client*, client);
	}
	FD_ZERO(&(g_zappy.network.read_fds));
	close(g_zappy.network.fd);
	printf("Server disconnected.\n");
}
