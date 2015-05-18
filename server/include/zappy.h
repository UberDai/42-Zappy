/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zappy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/14 22:50:39 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/18 03:19:26 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZAPPY_H
# define ZAPPY_H

# include <stdio.h>
# include <sys/select.h>

# define FOOD_DURATION	126
# define MAX_LEVEL		8
# define ITEM_COUNT		7

# define ITEM_FOOD		0
# define ITEM_LINEMATE	1
# define ITEM_DERAUMERE	2
# define ITEM_SIBUR		3
# define ITEM_MENDIANE	4
# define ITEM_PHIRAS	5
# define ITEM_THYSTAME	6

# define MAX_CLIENTS	10

typedef unsigned int	t_uint;
typedef unsigned short	t_ushort;

typedef struct s_client	t_client;

typedef struct			s_tile
{
	int					x;
	int					y;
	t_uint				client_count;
	t_client			**clients;
	short				refresh_client_list;
	t_uint				items[ITEM_COUNT];
}						t_tile;

struct					s_client
{
	t_uint				id;
	int					fd;
	t_ushort			level;
	t_tile				*position;
	t_uint				items[ITEM_COUNT];
	t_uint				hunger;
	struct s_client		*next;
};

typedef struct			s_time
{
	double				clock;
	t_uint				cycle_duration;
	t_uint				cycle_count;
}						t_time;

typedef struct			s_network
{
	t_uint				port;
	int					fd;
	fd_set				fd_set;
}						t_network;

typedef struct			s_zappy
{
	t_network			network;
	t_time				time;
	t_uint				client_count;
	t_uint				width;
	t_uint				height;
	t_tile				***map;
	t_uint				team_count;
	char				**teams;
	t_client			*clients;
}						t_zappy;

t_zappy					g_zappy;

void					map_init(void);
void					tile_update_client_list(t_tile *tile);
t_tile					*tile_at(int x, int y);

void					options_parse(t_uint ac, char **av);
void					options_valid(void);

int						die(const char *message);
void					usage(void);
double					get_time(void);

short					client_eat(t_client *client);
t_client				*client_create(t_tile *position);
void					client_delete(t_client *client_to_delete);
short					client_promote(t_client *client);
short					client_move(t_client *client, t_tile *tile);

void					network_bind();
void					network_listen();

#endif