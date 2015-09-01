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

#ifndef ACTIONSEE_HEADER
#define ACTIONSEE_HEADER

#include <string>
#include <iostream>
#include "Action.hpp"
#include "Client.hpp"

class Client;

class ActionSee : public Action
{
public:
	ActionSee(Client *);
	ActionSee(ActionSee const &);
	virtual ~ActionSee();
	std::string	toString() const;

	ActionSee	&operator=(ActionSee const &);

	virtual int	execute(Network &);
private:
	Client			*_client;
};

std::ostream	&operator<<(std::ostream &, ActionSee const &);

#endif /*ACTIONSEE_HEADER*/
