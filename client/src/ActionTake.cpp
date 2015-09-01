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

#include "ActionTake.hpp"

ActionTake::ActionTake(Inventory &inventory) :
	_inventory(inventory)
{

}

ActionTake::ActionTake(ActionTake const &model) :
	_obj(model._obj),
	_inventory(model._inventory)
{
	*this = model;
}

ActionTake::~ActionTake()
{

}

std::string		ActionTake::toString() const
{
	return "ActionTake";
}

ActionTake		&ActionTake::operator=(ActionTake const &copy)
{
	if (this != &copy)
	{
		_obj = copy._obj;
		_inventory = copy._inventory;
	}
	return *this;
}

std::ostream	&operator<<(std::ostream &o, ActionTake const &i)
{
	o << i.toString();
	return o;
}

int	ActionTake::execute(Network &network)
{
	std::string			message = Action::TAKE;
	std::string			data;

	message += _obj;
	data = network.send(message);

	if (data == Network::MSG_SUCCESS)
	{
		_inventory.add(_obj, 1);
		client->map[client->getPlayerX()][client->getPlayerY()].add(_obj, -1);
		return _successIndex;
	}
	return _failIndex;
}

void	ActionTake::setObject(const std::string &obj) { _obj = obj; }
