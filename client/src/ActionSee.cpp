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
