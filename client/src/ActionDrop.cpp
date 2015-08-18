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

#include "ActionDrop.hpp"
#include <sstream>

ActionDrop::ActionDrop(Inventory &inventory) :
	_inventory(inventory)
{

}

ActionDrop::ActionDrop(ActionDrop const &model) :
	_object(model._object),
	_inventory(model._inventory)
{
	*this = model;
}

ActionDrop::~ActionDrop()
{

}

std::string		ActionDrop::toString() const
{
	std::stringstream	ss;

	ss
		<< "ActionDrop : " << _object
	;
	return ss.str();
}

ActionDrop		&ActionDrop::operator=(ActionDrop const &copy)
{
	if (this != &copy)
		(void)copy;
	return *this;
}

std::ostream	&operator<<(std::ostream &o, ActionDrop const &i)
{
	o << i.toString();
	return o;
}

int				ActionDrop::execute(Network &network)
{
	std::string			message = DROP;
	std::string			data;

	message += _object;
	data = network.send(message);

	if (data == Network::MSG_SUCCESS)
	{
		_inventory.add(_object, -1);
		return _successIndex;
	}
	return _failIndex;
}

void			ActionDrop::setObject(const std::string &obj) { _object = obj; }
