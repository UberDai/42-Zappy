/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 02:42:59 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 21:11:19 by amaurer          ###   ########.fr       */
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

void		network_bind(void)
{
	struct sockaddr_in	server;
	int					option;

	if ((g_zappy.network.fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		die("Could not create the network socket.");
	option = 1;
	if (setsockopt(g_zappy.network.fd, SOL_SOCKET, SO_REUSEADDR, &option,
		sizeof(option)) == -1)
		die("The port is still in use.");
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(g_zappy.network.port);
	if (bind(g_zappy.network.fd, (struct sockaddr *)&server,
		sizeof(server)) < 0)
		die("Could not bind the server to the network.");
	if (listen(g_zappy.network.fd, 10))
		die("Error: listen()");
	FD_ZERO(&g_zappy.network.read_fds);
	FD_ZERO(&g_zappy.network.write_fds);
	FD_SET(g_zappy.network.fd, &g_zappy.network.read_fds);
	FD_SET(g_zappy.network.fd, &g_zappy.network.write_fds);
	printf("Listening on port %u\n", g_zappy.network.port);
}

void		network_client_disconnect(t_client *client)
{
	logger_client_disconnect(client);
	close(client->fd);
	FD_CLR(client->fd, &g_zappy.network.read_fds);
	FD_CLR(client->fd, &g_zappy.network.write_fds);
	if (client->status == STATUS_PLAYER)
		gfx_client_disconnect(client);
	client_delete(client);
}

void		network_disconnect(void)
{
	t_client	*client;

	printf("\n");
	while (g_zappy.clients->size > 0
		&& (client = lst_data_at(g_zappy.clients, 0)))
		network_client_disconnect(client);
	while (g_zappy.gfx_clients->size > 0
		&& (client = lst_data_at(g_zappy.gfx_clients, 0)))
		network_client_disconnect(client);
	FD_ZERO(&g_zappy.network.read_fds);
	FD_ZERO(&g_zappy.network.write_fds);
	close(g_zappy.network.fd);
	printf("Server disconnected.\n");
}

void		network_client_connect(void)
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
