#ifndef ACTIONINVENTORY_HPP
#define ACTIONINVENTORY_HPP

#include <string>
#include <iostream>
#include "Action.hpp"

class ActionInventory : public Action
{
public:
	ActionInventory();
	ActionInventory(ActionInventory const &);
	virtual ~ActionInventory();
	std::string	toString() const;

	ActionInventory	&operator=(ActionInventory const &);

	virtual int	execute(Network &);
};

std::ostream	&operator<<(std::ostream &, ActionInventory const &);

#endif /*ACTIONINVENTORY_HPP*/
