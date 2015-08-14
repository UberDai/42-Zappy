
#include "zappy.h"

t_egg	*egg_create(const t_client *client)
{
	t_egg	*egg;

	egg = calloc(1, sizeof(t_egg));
	egg->team = client->team;
	egg->hatch_time = g_zappy.time.cycle_count + EGG_MATURATION;
	lst_push_back(g_zappy.eggs, egg);

	return (egg);
}

void	egg_hatch(t_egg *egg)
{
	char	str[18] = { 0 };
	size_t	client_count;

	egg->team->max_clients++;
	lst_remove(g_zappy.eggs, lst_index_of(g_zappy.eggs, egg));

	client_count = team_count_clients(egg->team);
	snprintf(str, 17, "places libres %lu", client->team->max_clients - client_count);

	network_send_team(egg->team, str);
	free(egg);
}
