/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zappy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/14 22:50:39 by amaurer           #+#    #+#             */
/*   Updated: 2015/08/16 00:07:08 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZAPPY_H
# define ZAPPY_H

# include <stdio.h>
# include <sys/select.h>
# include "ftlst.h"

# define FOOD_DURATION		126
# define CLIENT_BASE_FOOD	10
# define MAX_LEVEL			8
# define CLIENT_QUEUE_MAX	10

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

# define REGEN_RATE			FOOD_DURATION
# define REGEN_MAX			2
# define REGEN_PROBABILITY	5

# define EGG_MATURATION		600

# define NET_SUCCESS		"ok"
# define NET_FAILURE		"ko"

# define STATUS_UNKNOWN		0
# define STATUS_PLAYER		1
# define STATUS_EGG			2
# define STATUS_GFX			3

# define COMMAND_NONE		-1
# define COMMAND_FAIL		0
# define COMMAND_SUCCESS	1

typedef unsigned int		t_uint;
typedef unsigned short		t_ushort;
typedef char				t_bool;

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
	char					*name;
	t_uint					max_clients;
}							t_team;

typedef struct				s_command
{
	char					*name;
	t_uint					delay;
	short					(*pre_func)(t_client *, t_uint, char **);
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
	t_lst					clients;
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

typedef struct				s_egg
{
	t_team					*team;
	t_tile					*position;
	t_uint					hatch_time;
	char					has_hatched;
}							t_egg;

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
	t_lst					*teams;
	t_uint					max_clients;
	t_lst					*clients;
	t_lst					*gfx_clients;
	t_lst					*anonymous_clients;
	t_lst					*eggs;
	short					paused;
}							t_zappy;

t_zappy						g_zappy;
char						*g_item_names[ITEM_COUNT];

void						map_init(void);
t_tile						*tile_at(int x, int y);
short						tile_add_item(t_tile *tile, int item);
short						tile_remove_item(t_tile *tile, int item);
void						tile_regenerate(t_tile *tile);
char						*tile_content(t_tile *tile, t_client *client);
void						map_regenerate(void);
char						*append_string(char *src, const char *str);

void						options_parse(t_uint ac, char **av);
void						options_valid(void);

int							die(const char *message);
void						usage(void);
void						print_client(t_client *client);
void						print_client_queue(t_client *client);
void						print_tile(t_tile *tile);
void						print_client_positions(void);
double						get_time(void);
int							rand_range(int min, int max);

short						client_eat(t_client *client);
short						client_move(t_client *client);
short						client_rotate(t_client *client, short angle);
t_client					*client_create(void);
void						client_set_spawn_position(t_client *client);
void						client_delete(t_client *client_to_delete);
short						client_promote(t_client *client);
short						client_can_promote(t_client *client);
short						client_move_to(t_client *client, t_tile *tile);
short						client_queue_push(t_client *client, t_command *command, char **av);
short						client_queue_push_front(t_client *client, t_command *command, char **av);
void						client_queue_shift(t_client *client);
void						client_queue_free(t_client *client);
void						client_set_team(t_client *client, const char *team_name);
short						client_add_item(t_client *client, int item);
short						client_remove_item(t_client *client, int item);
short						client_pick(t_client *client, int item);
short						client_drop(t_client *client, int item);
char						*client_inventory(t_client *client);
void						client_broadcast(t_client *emitter, char *message);

t_team						*team_get(const char *name);
t_team						*team_create(const char *team_name);
size_t						team_count_clients(t_team *team);

void						network_bind();
void						network_receive(void);
void						network_send(t_client *client, const char *str, int options);
void						network_send_team(const t_team *team, const char *str);
void						network_client_disconnect(t_client *client);
void						network_disconnect(void);

char						command_parse(t_client *client, char *input);
short						command_right(t_client *client, t_uint argc, char **argv);
short						command_left(t_client *client, t_uint argc, char **argv);
short						command_move(t_client *client, t_uint argc, char **argv);
short						command_fork(t_client *client, t_uint argc, char **argv);
short						command_pick(t_client *client, t_uint argc, char **argv);
short						command_drop(t_client *client, t_uint argc, char **argv);
short						command_pause(t_client *client, t_uint argc, char **argv);
short						command_resume(t_client *client, t_uint argc, char **argv);
short						command_inventory(t_client *client, t_uint argc, char **argv);
short						command_connect_count(t_client *client, t_uint argc, char **argv);
short						command_fork(t_client *client, t_uint argc, char **argv);
short						command_promote(t_client *client, t_uint argc, char **argv);
short						command_pre_promote(t_client *client, t_uint argc, char **argv);
short						command_expulse(t_client *client, t_uint argc, char **argv);
short						command_see(t_client *client, t_uint argc, char **argv);
short						command_broadcast(t_client *client, t_uint argc, char **argv);

void						signal_bind(void);

void						zappy_run(void);
void						zappy_pause(t_client *client);
void						zappy_resume(t_client *client);

void						gfx_client_connect(t_client *client, t_client *gfx_client);
void						gfx_client_disconnect(t_client *client);
void						gfx_client_death(t_client *client);
void						gfx_tile_add(t_client *client, t_tile *tile, int item);
void						gfx_tile_remove(t_client *client, t_tile *tile, int item);
void						gfx_egg_add(const t_egg *egg);
void						gfx_egg_remove(const t_egg *egg);
void						gfx_client_pick(t_client *client, int item);
void						gfx_client_drop(t_client *client, int item);
void						gfx_client_move_to(t_client *client, t_tile *tile);
void						gfx_client_turn(t_client *client);
void						gfx_send_map(t_client *client);
void						gfx_send_clients(t_client *client);

t_lst						*get_vision(t_client *client);

t_egg						*egg_create(const t_client *client);
void						egg_remove(t_egg *egg);
void						egg_hatch(t_egg *egg);
t_egg						*get_hatched_egg(const t_team *team);
void						watch_eggs(void);

#endif
