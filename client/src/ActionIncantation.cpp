#include "ActionIncantation.hpp"

ActionIncantation::ActionIncantation(Client *client) :
_client(client)
{

}

ActionIncantation::ActionIncantation(ActionIncantation const &model)
{
	*this = model;
}

ActionIncantation::~ActionIncantation()
{

}

std::string			ActionIncantation::toString() const
{
	return "ActionIncantation";
}

ActionIncantation	&ActionIncantation::operator=(ActionIncantation const &copy)
{
	if (this != &copy)
		_client = copy._client;
	return *this;
}

std::ostream		&operator<<(std::ostream &o, ActionIncantation const &i)
{
	o << i.toString();
	return o;
}

int					ActionIncantation::execute(Network &network)
{
	std::string			data;

	data = network.send(INCANTATION);

	if (data == Network::MSG_ELEVATION)
	{
		data = network.recieve();

		if (data.find(Network::MSG_CURRENT_LVL) != 0)
			return _failIndex;

		data = data.substr(Network::MSG_CURRENT_LVL.size());

		/*   TEST    */
		std::map<std::string, size_t>	&compo = _client->getTotems()[_client->getLevel()];
		for (auto &kv : compo)
		{
			std::string::size_type i = _client->fov[0].find(kv.first);
			if (i != std::string::npos)
				_client->fov[0].erase(i, kv.first.length());
		}

		/*   TEST    */
		_client->setLevel(std::stoi(data));
		return _successIndex;
	}
	return _failIndex;
}
