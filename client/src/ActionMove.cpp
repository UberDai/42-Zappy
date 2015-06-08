#include "ActionMove.hpp"

std::map<enum eDirection, std::string>	ActionMove::_directionMap =
{
	{ UP,			MOVE_FORWARD },
	{ TURN_LEFT,	MOVE_LEFT },
	{ TURN_RIGHT,	MOVE_RIGHT }
}
;

ActionMove::ActionMove(enum eDirection dir) :
_dir(dir)
{

}

ActionMove::ActionMove(ActionMove const &model)
{
	*this = model;
}

ActionMove::~ActionMove()
{

}

std::string		ActionMove::toString() const
{
	return "ActionMove";
}

ActionMove		&ActionMove::operator=(ActionMove const &copy)
{
	if (this != &copy)
		(void)copy;
	return *this;
}

std::ostream	&operator<<(std::ostream &o, ActionMove const &i)
{
	o << i.toString();
	return o;
}

int				ActionMove::execute(Network &network)
{
	std::string		ret;

	ret = network.send(_directionMap[_dir]);

	if (ret == Network::MSG_SUCCESS)
	{
		switch (_dir)
		{
			case UP:
			switch (client->getPlayerOrientation())
			{
				case NORTH:
				client->setPlayerY(client->getPlayerY() + 1);
				break;
				case SOUTH:
				client->setPlayerY(client->getPlayerY() - 1);
				break;
				case EAST:
				client->setPlayerX(client->getPlayerX() + 1);
				break;
				case WEST:
				client->setPlayerX(client->getPlayerX() - 1);
				break;
			}
			break;
			case TURN_LEFT:
			client->setPlayerOrientation(static_cast<enum eOrientation>((client->getPlayerOrientation() + 1) % 4));
			break;
			case TURN_RIGHT:
			client->setPlayerOrientation(static_cast<enum eOrientation>((client->getPlayerOrientation() - 1) % 4));
			break;

		}
		return _successIndex;
	}
	return _failIndex;
}

void			ActionMove::setDirection(enum eDirection dir) { _dir = dir; }
