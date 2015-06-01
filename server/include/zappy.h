/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zappy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/14 22:50:39 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/31 23:08:45 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZAPPY_H
# define ZAPPY_H

# include <stdio.h>
# include <sys/select.h>
# include "dlist.h"

# define FOOD_DURATION		126
# define CLIENT_BASE_FOOD	10
# define MAX_LEVEL			8
# define CLIENT_QUEUE_MAX	5

# define ITEM_COUNT			7
# define ITEM_FOOD			0
# define ITEM_LINEMATE		1
# define ITEM_DERAUMERE		2
# define ITEM_SIBUR			3
# define ITEM_MENDIANE		4
# define ITEM_PHIRAS		5
# define ITEM_THYSTAME		6

# define SELECT_TIMEOUT		0

# define TURN_LEFT			-1
# define TURN_RIGHT			1

# define NET_SEND_ALL		1
# define NET_SEND_CLIENT	2
# define NET_SEND_GFX		4

# define REGEN_RATE			10
# define REGEN_MAX			3

# define NET_SUCCESS		"yay"
# define NET_FAILURE		"nope"

# define STATUS_UNKNOWN		0
# define STATUS_PLAYER		1
# define STATUS_EGG			2
# define STATUS_GFX			3

typedef unsigned int		t_uint;
typedef unsigned short		t_ushort;

typedef enum 				e_orient
{
	ORIENT_NORTH = 1,
	ORIENT_EAST,
	ORIENT_SOUTH,
	ORIENT_WEST
}							t_orient;

typedef struct s_client		t_client;

typedef struct				s_team
{
	t_dlist					dlist;
	char					*name;
	t_uint					max_clients;
}							t_team;

typedef struct				s_command
{
	char					*name;
	t_uint					delay;
	short					(*func)(t_client *, t_uint, char **);
}							t_command;

typedef struct				s_queue
{
	short					set;
	size_t					ac;
	char					**av;
	t_command				*command;
	t_uint					delay;
}							t_queue;

typedef struct				s_tile
{
	int						x;
	int						y;
	t_uint					client_count;
	t_client				**clients;
	short					refresh_client_list;
	t_uint					items[ITEM_COUNT];
	t_queue					queue[CLIENT_QUEUE_MAX];
}							t_tile;

struct						s_client
{
	struct s_client			*next;
	struct s_client			*prev;
	t_uint					id;
	int						fd;
	short					status;
	t_ushort				level;
	t_team					*team;
	t_tile					*position;
	t_orient				orientation;
	t_uint					items[ITEM_COUNT];
	t_uint					hunger;
	t_queue					queue[CLIENT_QUEUE_MAX];
};

typedef struct				s_time
{
	double					clock;
	t_uint					cycle_duration;
	t_uint					cycle_count;
	double					next_cycle;
}							t_time;

typedef struct				s_network
{
	t_uint					port;
	int						fd;
	fd_set					read_fds;
}							t_network;

typedef struct				s_zappy
{
	t_network				network;
	t_time					time;
	t_uint					width;
	t_uint					height;
	t_tile					***map;
	t_uint					team_count;
	t_team					*teams;
	t_uint					client_count;
	t_uint					max_clients;
	t_client				*clients;
	t_client				*gfx_clients;
	t_client				*anonymous_clients;
	short					paused;
}							t_zappy;

t_zappy						g_zappy;

void						map_init(void);
void						tile_update_client_list(t_tile *tile);
t_tile						*tile_at(int x, int y);
short						tile_add_item(t_tile *tile, int item);
short						tile_remove_item(t_tile *tile, int item);
void						tile_regenerate(t_tile *tile);
void						map_regenerate(void);

void						options_parse(t_uint ac, char **av);
void						options_valid(void);

int							die(const char *message);
void						usage(void);
void						print_client(t_client *client);
void						print_client_queue(t_client *client);
void						print_tile(t_tile *tile);
double						get_time(void);
int							rand_range(int min, int max);

short						client_eat(t_client *client);
short						client_move(t_client *client);
short						client_rotate(t_client *client, short angle);
t_client					*client_create(void);
void						client_delete(t_client *client_to_delete);
short						client_promote(t_client *client);
short						client_move_to(t_client *client, t_tile *tile);
short						client_queue_push(t_client *client, t_command *command, char **av);
void						client_queue_shift(t_client *client);
void						client_queue_free(t_client *client);
void						client_set_team(t_client *client, const char *team_name);
short						client_add_item(t_client *client, int item);
short						client_remove_item(t_client *client, int item);
short						client_pick(t_client *client, int item);
short						client_drop(t_client *client, int item);

t_team						*team_get(const char *name);
t_team						*team_create(const char *team_name);
size_t						team_clients_count(t_team *team);

void						network_bind();
void						network_receive(void);
void						network_send(t_client *client, char *str, int options);
t_client 					*network_client_disconnect(t_client *client);
void						network_disconnect(void);

t_client					*command_parse(t_client *client, char *input);
short						command_right(t_client *client, t_uint argc, char **argv);
short						command_left(t_client *client, t_uint argc, char **argv);
short						command_move(t_client *client, t_uint argc, char **argv);
short						command_pick(t_client *client, t_uint argc, char **argv);
short						command_drop(t_client *client, t_uint argc, char **argv);
short						command_pause(t_client *client, t_uint argc, char **argv);
short						command_resume(t_client *client, t_uint argc, char **argv);

void						signal_bind(void);

void						zappy_run(void);
void						zappy_pause(t_client *client);
void						zappy_resume(t_client *client);

void						gfx_client_connect(t_client *client);
void						gfx_client_disconnect(t_client *client);
void						gfx_client_death(t_client *client);
void						gfx_tile_add(t_client *client, t_tile *tile, int item);
void						gfx_tile_remove(t_client *client, t_tile *tile, int item);

#endif
