/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/10 21:13:37 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 21:14:24 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void		logger_client_disconnect(const t_client *client)
{
	char	str[26];
	char	*header;

	bzero(str, 26);
	header = get_header(client);
	snprintf(str, 23, "%s\tDisconnect", header);
	free(header);
	logger_log(str);
}

void		logger_client_connect(const t_client *client)
{
	char	str[23];
	char	*header;

	bzero(str, 23);
	header = get_header(client);
	snprintf(str, 23, "%s\tConnect", header);
	free(header);
	logger_log(str);
}

void		logger_client_send(const t_client *client, const char *message)
{
	char	*str;
	char	*header;

	header = get_header(client);
	asprintf(&str, "%s\t<< %s", header, message);
	free(header);
	str[strlen(str) - 1] = 0;
	logger_log(str);
	free(str);
}

void		logger_client_receive(const t_client *client, const char *message)
{
	char	*str;
	char	*header;

	header = get_header(client);
	asprintf(&str, "%s\t>> %s", header, message);
	free(header);
	logger_log(str);
	free(str);
}
