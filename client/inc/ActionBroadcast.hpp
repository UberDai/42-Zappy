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

#ifndef ACTIONBROADCAST_HEADER
#define ACTIONBROADCAST_HEADER

# include <string>
# include <iostream>
# include "Action.hpp"

class ActionBroadcast : public Action
{
public:
	ActionBroadcast();
	ActionBroadcast(ActionBroadcast const &);
	virtual ~ActionBroadcast();
	std::string	toString() const;

	ActionBroadcast	&operator=(ActionBroadcast const &);

	virtual int			execute(Network &);
	void				setMessage(const std::string &);

private:
	std::string			_msg;
};

std::ostream	&operator<<(std::ostream &o, ActionBroadcast const &i);

#endif /*ACTIONBROADCAST_HEADER*/
