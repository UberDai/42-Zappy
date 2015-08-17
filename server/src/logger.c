/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/16 01:37:34 by amaurer           #+#    #+#             */
/*   Updated: 2015/08/16 02:42:04 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static char	*get_header(const t_client *client)
{
	char	*str;
	char	type;

	if (client->status == STATUS_PLAYER)
		type = 'P';
	else if (client->status == STATUS_GFX)
		type = 'G';
	else
		type = '?';

	asprintf(&str, "[%c_%03u]", type, client->id);

	return (str);
}

void	logger_init(const char *filename)
{
	g_zappy.logger_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
}

void	logger_log(const char *message)
{
	if (g_zappy.logger_fd <= 0)
		return ;
	write(g_zappy.logger_fd, message, strlen(message));
	write(g_zappy.logger_fd, "\n", 1);
}

void	logger_close(void)
{
	close(g_zappy.logger_fd);
}

void	logger_client_disconnect(const t_client *client)
{
	char str[26] = { 0 };
	char	*header;

	header = get_header(client);
	snprintf(str, 23, "%s\tDisconnect", header);
	free(header);
	logger_log(str);
}

void	logger_client_connect(const t_client *client)
{
	char	str[23] = { 0 };
	char	*header;

	header = get_header(client);
	snprintf(str, 23, "%s\tConnect", header);
	free(header);
	logger_log(str);
}

void	logger_client_send(const t_client *client, const char *message)
{
	char	*str;
	char	*header;

	header = get_header(client);
	asprintf(&str, "%s\t<< %s", header, message);
	free(header);
	str[strlen(str) - 1] = 0;
	logger_log(str);
}

void	logger_client_receive(const t_client *client, const char *message)
{
	char	*str;
	char	*header;

	header = get_header(client);
	asprintf(&str, "%s\t>> %s", header, message);
	free(header);
	logger_log(str);
}
