/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 02:42:59 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/18 03:32:11 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define NETWORK_BUFFER_SIZE	200

void		network_bind()
{
	struct sockaddr_in	server;

	if ((g_zappy.network.fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		die("Could not create the network socket.");

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(g_zappy.network.port);

	if (bind(g_zappy.network.fd, (struct sockaddr *) &server, sizeof(server)) < 0)
		die("Could not bind the server to the network.");

	printf("Listening on port %u\n", g_zappy.network.port);
}

static void	network_client_connect(void)
{
	t_client			*client;
	struct sockaddr_in	sin;
	socklen_t			sin_size;

	sin_size = sizeof(struct sockaddr_in);
	bzero(&sin, sin_size);
	client = client_create(g_zappy.map[1][1]);
	client->fd = accept(g_zappy.network.fd, (struct sockaddr *)&sin, &sin_size);

	if (client->fd == -1)
		die("Client connection error.");

	FD_SET(client->fd, &(g_zappy.network.fd_set));
	ft_putendl("Client created.");
}

static void	network_client_data(t_client *client)
{
	char	buffer[NETWORK_BUFFER_SIZE] = { 0 };
	int		ret;

	ret = read(client->fd, buffer, NETWORK_BUFFER_SIZE - 1);

	if (ret == -1)
		die("Could not read the client.");
	else if (ret == 0)
	{
		close(client->fd);
		FD_CLR(client->fd, &(g_zappy.network.fd_set));
		client_delete(client);
	}
	else
	{
		ft_putendl(buffer);
	}
}

void		network_listen(void)
{
	t_client	*client;

	if (listen(g_zappy.network.fd, 10))
		die("Error: listen()");

	FD_ZERO(&(g_zappy.network.fd_set));
	FD_SET(g_zappy.network.fd, &(g_zappy.network.fd_set));

	while (1)
	{
		if (select(FD_SETSIZE, &(g_zappy.network.fd_set), NULL, NULL, NULL) < 0)
			die("Error: select()");

		if (FD_ISSET(g_zappy.network.fd, &(g_zappy.network.fd_set)))
			network_client_connect();
		else
		{
			client = g_zappy.clients;
			while (client)
			{
				if (FD_ISSET(client->fd, &(g_zappy.network.fd_set)))
					network_client_data(client);
				client = client->next;
			}
		}
	}
}