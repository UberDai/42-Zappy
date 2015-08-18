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

#include "ActionBroadcast.hpp"
#include <sstream>

ActionBroadcast::ActionBroadcast()
{

}

ActionBroadcast::ActionBroadcast(ActionBroadcast const &model) :
	_msg(model._msg)
{
	*this = model;
}

ActionBroadcast::~ActionBroadcast()
{

}

std::string		ActionBroadcast::toString() const
{
	std::stringstream	ss;

	ss
		<< "ActionBroadcast : " << _msg
	;
	return ss.str();
}

ActionBroadcast	&ActionBroadcast::operator=(ActionBroadcast const &copy)
{
	if (this != &copy)
		(void)copy;
	return *this;
}

std::ostream	&operator<<(std::ostream &o, ActionBroadcast const &i)
{
	o << i.toString();
	return o;
}

int				ActionBroadcast::execute(Network &network)
{
	std::string		ret;

	ret = network.send(BROADCAST + _msg);

	if (ret == Network::MSG_SUCCESS)
		return _successIndex;
	return _failIndex;
}

void			ActionBroadcast::setMessage(const std::string &msg)
{
	_msg = msg;
}
