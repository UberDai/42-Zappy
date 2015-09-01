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

#ifndef ACTIONDROP_HEADER
#define ACTIONDROP_HEADER

#include <string>
#include <iostream>
#include "Action.hpp"
#include "Inventory.hpp"

class Inventory;

class ActionDrop : public Action
{
public:
	ActionDrop(Inventory &);
	ActionDrop(ActionDrop const &);
	virtual ~ActionDrop();
	std::string	toString() const;

	ActionDrop	&operator=(ActionDrop const &);

	virtual int			execute(Network &);
	void				setObject(const std::string &);

private:
	std::string			_object;
	Inventory			&_inventory;
};

std::ostream	&operator<<(std::ostream &, ActionDrop const &);

#endif /*ACTIONDROP_HEADER*/
