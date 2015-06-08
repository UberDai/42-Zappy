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
	// int i = 0;
	Map			&m = _client->getMap();

	ret = network.send(SEE);
	m.setFrom(_client->getPlayerX(), _client->getPlayerY(), _client->getPlayerOrientation(), ret);
	return _successIndex;
	/*
	parse du retour en n string/inventaire
	getplayerX/Y
	set map[X][Y] = parse[0]
	....
	set map[X + ?][Y + ?] = parse[?]
	*/
	//si nourriture case 0 add prend nourriture
}
