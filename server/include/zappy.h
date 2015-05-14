/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zappy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/14 22:50:39 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/15 01:24:02 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZAPPY_H
# define ZAPPY_H

# define FOOD_DURATION	126

typedef unsigned int	t_uint;

typedef enum			e_item
{
	FOOD,
	LINEMATE,
	DERAUMERE,
	SIBUR,
	MENDIANE,
	PHIRAS,
	THYSTAME
}						e_item;

typedef struct			s_vector
{
	int					x;
	int					y;
}						t_vector;

typedef struct			s_item
{
	e_item				type;
	struct s_item		*next;
}						t_item;

typedef struct			s_inventory
{
	t_uint				food_count;
	t_uint				linemate_count;
	t_uint				deraumere_count;
	t_uint				sibur_count;
	t_uint				mendiane_count;
	t_uint				phiras_count;
	t_uint				thystame_count;
	t_item				*items;
}						t_inventory;

typedef struct			s_tile
{
	t_vector			position;
	t_inventory			inventory;
}						t_tile;


typedef struct			s_player
{
	t_tile				tile;
	t_inventory			inventory;
	struct s_player		*next;
}						t_player;

typedef struct			s_zappy
{
	t_uint				port;
	t_uint				clock;
	t_uint				client_count;
	t_uint				width;
	t_uint				height;
	t_tile				***map;
	t_uint				nb_team;
	char				**teams;
	t_player			*players;
}						t_zappy;

t_zappy					g_zappy;

void					map_init(void);
void					options_parse(t_uint ac, char **av);
int						die(const char *message);

#endif