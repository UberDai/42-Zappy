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

#include "Pathfinding.hpp"
#include "eOrientation.hpp"
#include "Client.hpp"

Pathfinding::Pathfinding(Client & client) :
	_client(client)
{

}

Pathfinding::Pathfinding(Pathfinding const &model) :
	_client(model._client)
{
	*this = model;
}

Pathfinding::~Pathfinding()
{

}

std::string	Pathfinding::toString() const
{
	return "Pathfinding";
}

Pathfinding&	Pathfinding::operator=(Pathfinding const &copy)
{
	if (this != &copy)
		(void)copy;
	return *this;
}

std::ostream	&operator<<(std::ostream &o, Pathfinding const &i)
{
	o << i.toString();
	return o;
}

int Pathfinding::getTotalCase(int k)
{
	return (2 * k + 1) * (2 * k + 1);
}

int Pathfinding::getNbcircle(int n)
{
	int i;

	for (i = 0; getTotalCase(i) <= n; i++)
		;
	return i;
}

int Pathfinding::getCirclePos(int n)
{
	int circle = getNbcircle(n);
	return ((8 * circle + (n - getTotalCase(circle)) + 1)) % (8 * circle);
}

void Pathfinding::getOffset(int circle, int pos, int XY[2])
{
	int q = pos / (2 * circle);
	int r = pos - q * 2 * circle;

	switch (q)
	{
		case 0:
			XY[0] += 0;
			XY[1] += r;
			break;
		case 1:
			XY[1] += 2 * circle;
			XY[0] += r;
			break;
		case 2:
			XY[0] += 2 * circle;
			XY[1] += 2 * circle - r;
			break;
		default:
			XY[1] += 0;
			XY[0] += 2 * circle - r;
			break;
	}
}

void Pathfinding::Pos(int n, int XY[2])
{
	int circle = getNbcircle(n);
	int pos = getCirclePos(n);

	XY[0] = -circle;
	XY[1] = -circle;
	getOffset(circle, pos, XY);
}

void	Pathfinding::pathfinding(std::pair<size_t, size_t> start, std::pair<size_t, size_t> end)
{
	std::pair<int, int>	mov;
	eOrientation dir = _client.getPlayerOrientation();

	mov.first = abs((int)(end.first - start.first)) < (int)_client.map.getMapX() / 2
	? end.first - start.first
	: start.first > _client.map.getMapX() / 2
	? start.first - (_client.map.getMapX() + end.first)
	: start.first - (_client.map.getMapX() - end.first);

	mov.second = abs((int)(end.second - start.second)) < (int)_client.map.getMapY() / 2
	? end.second - start.second
	: start.second > _client.map.getMapY() / 2
	? start.second - (_client.map.getMapY() + end.second)
	: start.second - (_client.map.getMapY() - end.second);

	_client.printDebug("mov first " + std::to_string(mov.first) + " mov second " + std::to_string(mov.second));
	if (mov.first < 0)
	{
		switch (dir)
		{
			case NORTH:
				_client.actions.push_back(Action::create(Action::MOVE_LEFT));
				dir = WEST;
				break ;
			case SOUTH:
				_client.actions.push_back(Action::create(Action::MOVE_RIGHT));
				dir = WEST;
				break ;
			case EAST:
				_client.actions.push_back(Action::create(Action::MOVE_RIGHT));
				_client.actions.push_back(Action::create(Action::MOVE_RIGHT));
				dir = WEST;
				break ;
			default:
				break ;
		}
	}
	else if (mov.first > 0)
	{
		switch (dir)
		{
			case NORTH:
				_client.actions.push_back(Action::create(Action::MOVE_RIGHT));
				dir = EAST;
				break ;
			case SOUTH:
				_client.actions.push_back(Action::create(Action::MOVE_LEFT));
				dir = EAST;
				break ;
			case WEST:
				_client.actions.push_back(Action::create(Action::MOVE_RIGHT));
				_client.actions.push_back(Action::create(Action::MOVE_RIGHT));
				dir = EAST;
				break ;
			default:
				break ;
		}
	}
	for (int i = 0; i < abs(mov.first); ++i)
		_client.actions.push_back(Action::create(Action::MOVE_FORWARD));

	if (mov.second < 0)
	{
		switch (dir)
		{
			case NORTH:
				_client.actions.push_back(Action::create(Action::MOVE_RIGHT));
				_client.actions.push_back(Action::create(Action::MOVE_RIGHT));
				break ;
			case WEST:
				_client.actions.push_back(Action::create(Action::MOVE_LEFT));
				break ;
			case EAST:
				_client.actions.push_back(Action::create(Action::MOVE_RIGHT));
				break ;
			default:
				break ;
		}
	}
	else if (mov.second > 0)
	{
		switch (dir)
		{
			case SOUTH:
				_client.actions.push_back(Action::create(Action::MOVE_RIGHT));
				_client.actions.push_back(Action::create(Action::MOVE_RIGHT));
				break ;
			case EAST:
				_client.actions.push_back(Action::create(Action::MOVE_LEFT));
				break ;
			case WEST:
				_client.actions.push_back(Action::create(Action::MOVE_RIGHT));
				break ;
			default:
				break ;
		}
	}
	for (int i = 0; i < abs(mov.second); ++i)
		_client.actions.push_back(Action::create(Action::MOVE_FORWARD));
}

size_t Pathfinding::getCaseX(int i)
{
	int tmp;

	tmp = _client.getPlayerX() + i;

	if (tmp < 0)
		return _client.map.getMapX() + tmp;
	else if (tmp >= (int)_client.map.getMapX())
		return _client.map.getMapX() -1 != 0 ? tmp % (_client.map.getMapX() -1) : tmp;
	return tmp;
}

size_t Pathfinding::getCaseY(int i)
{
	int tmp;

	tmp = _client.getPlayerY() + i;

	if (tmp < 0)
		return _client.map.getMapY() + tmp;
	else if (tmp >= (int)_client.map.getMapY())
		return _client.map.getMapY() - 1 != 0 ? tmp % (_client.map.getMapY() - 1) : tmp;
	return tmp;
}

std::pair<size_t, size_t>	Pathfinding::getPairCase(int x, int y)
{
	return std::make_pair<size_t, size_t>(getCaseX(x), getCaseY(y));
}