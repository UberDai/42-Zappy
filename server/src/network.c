/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 02:42:59 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/22 02:02:51 by amaurer          ###   ########.fr       */
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

#define NETWORK_BUFFER_SIZE	500

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
	client = client_create(g_zappy.map[1][1]);
	client->fd = accept(g_zappy.network.fd, (struct sockaddr *)&sin, &sin_size);

	if (client->fd == -1)
		die("Client connection error.");

	FD_SET(client->fd, &(g_zappy.network.read_fds));
	ft_putendl("Client created.");

	network_send(client, "BIENVENUE");
}

static void	network_client_data(t_client *client)
{
	char		buffer[NETWORK_BUFFER_SIZE] = { 0 };
	char		*input;
	int			ret;

	ret = read(client->fd, buffer, NETWORK_BUFFER_SIZE - 1);

	if (ret == -1)
		die("Could not read the client.");
	else if (ret == 0)
	{
		printf("Client #%u disconnected.\n", client->id);
		close(client->fd);
		FD_CLR(client->fd, &(g_zappy.network.read_fds));
		client_delete(client);
	}
	else
	{
		input = ft_strsub(buffer, 0, ft_strlen(buffer) - 1);
		command_parse(client, input);
		free(input);
	}
}

static void	network_select(double remaining_time)
{
	t_client				*client;
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
		client = g_zappy.clients;
		while (client)
		{
			if (FD_ISSET(client->fd, &read_fds))
				network_client_data(client);
			client = client->next;
		}
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

void		network_send(t_client *client, char *str)
{
	char	*output;

	output = ft_strnew(ft_strlen(str) + 1);
	ft_strcat(output, str);
	ft_strcat(output, "\n");
	send(client->fd, output, ft_strlen(output), 0);
	free(output);
}