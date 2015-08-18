/*      _           _          _           _             _            _          _      _
       / /\        /\ \       /\ \        _\ \          /\ \         /\ \       /\ \   /\_\
      / /  \       \ \ \     /  \ \      /\__ \        /  \ \       /  \ \     /  \ \ / / /         _
     / / /\ \__    /\ \_\   / /\ \ \    / /_ \_\      / /\ \ \     / /\ \ \   / /\ \ \\ \ \__      /\_\
    / / /\ \___\  / /\/_/  / / /\ \_\  / / /\/_/     / / /\ \_\   / / /\ \_\ / / /\ \ \\ \___\    / / /
    \ \ \ \/___/ / / /    / / /_/ / / / / /         / /_/_ \/_/  / /_/_ \/_// / /  \ \_\\__  /   / / /
     \ \ \      / / /    / / /__\/ / / / /         / /____/\    / /____/\  / / /   / / // / /   / / /
 _    \ \ \    / / /    / / /_____/ / / / ____    / /\____\/   / /\____\/ / / /   / / // / /   / / /
/_/\__/ / /___/ / /__  / / /\ \ \  / /_/_/ ___/\ / / /______  / / /      / / /___/ / // / /___/ / /
\ \/___/ //\__\/_/___\/ / /  \ \ \/_______/\__\// / /_______\/ / /      / / /____\/ // / /____\/ /
 \_____\/ \/_________/\/_/    \_\/\_______\/    \/__________/\/_/       \/_________/ \/_________/
*/

#include "ActionSee.hpp"
#include "Map.hpp"

ActionSee::ActionSee(Client *client) :
	_client(client)
{

}

ActionSee::ActionSee(ActionSee const &model)
{
	*this = model;
}

ActionSee::~ActionSee()
{

}

std::string		ActionSee::toString() const
{
	return "ActionSee";
}

ActionSee		&ActionSee::operator=(ActionSee const &copy)
{
	if (this != &copy)
		_client = copy._client;
	return *this;
}

std::ostream	&operator<<(std::ostream &o, ActionSee const &i)
{
	o << i.toString();
	return o;
}

int				ActionSee::execute(Network &network)
{
	std::string ret;
	std::string tmp;
	Map			&m = _client->getMap();

	ret = network.send(SEE);
	m.setFrom(_client->getPlayerX(), _client->getPlayerY(), _client->getPlayerOrientation(), ret);
	return _successIndex;
}
