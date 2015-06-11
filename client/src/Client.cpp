//               .-'''''-.
//             .'         `.
//            :             :        File       : Client.cpp
//           :               :       Creation   : 2015-05-21 00:44:59
//           :      _/|      :       Last Edit  : 2015-06-10 00:02:12
//            :   =/_/      :        Author     : nsierra-
//             `._/ |     .'         Mail       : nsierra-@student.42.fr
//          (   /  ,|...-'
//           \_/^\/||__
//        _/~  `""~`"` \_
//     __/  -'/  `-._ `\_\__
//   /jgs  /-'`  `\   \  \-

#include "Client.hpp"
#include "ErrorMsg.hpp"
#include "eDirection.hpp"
#include "Actions.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <regex>
#include <ctime>
#include <locale>

const std::regex	Client::_serverInfosFormat("(\\d+) (\\d+)");

Totems	Client::_totems =
{
	{
		{  }
	},
	{
		{ Inventory::LINEMATE, 1 }
	},
	{
		{ Inventory::LINEMATE, 1 },
		{ Inventory::DERAUMERE, 1 },
		{ Inventory::SIBUR, 1 }
	},
	{
		{ Inventory::LINEMATE, 2 },
		{ Inventory::SIBUR, 1 },
		{ Inventory::PHIRAS, 2 }
	},
	{
		{ Inventory::LINEMATE, 1 },
		{ Inventory::DERAUMERE, 1 },
		{ Inventory::SIBUR, 2 },
		{ Inventory::PHIRAS, 1 }
	},
	{
		{ Inventory::LINEMATE, 1 },
		{ Inventory::DERAUMERE, 2 },
		{ Inventory::SIBUR, 1 },
		{ Inventory::MENDIANE, 3 }
	},
	{
		{ Inventory::LINEMATE, 1 },
		{ Inventory::DERAUMERE, 2 },
		{ Inventory::SIBUR, 3 },
		{ Inventory::PHIRAS, 1 }
	},
	{
		{ Inventory::LINEMATE, 2 },
		{ Inventory::DERAUMERE, 2 },
		{ Inventory::SIBUR, 2 },
		{ Inventory::MENDIANE, 2 },
		{ Inventory::PHIRAS, 2 },
		{ Inventory::THYSTAME, 1 }
	}
}
;


Client::Client(unsigned int port, std::string teamName, std::string hostName) :
	_teamName(teamName),
	_network(new Network(this, port, hostName)),
	_level(1),
	_playerX(0),
	_playerY(0),
	_playerOrientation(NORTH)
{

	std::stringstream name;
	name << "debug/" << getpid();
	_ofs.open(name.str().c_str());

	_inventory.add(Inventory::FOOD, 10);
	Action::client = this;
}

Client::Client(Client const &src) :
_teamName(src._teamName)
{
	*this = src;
}

Client::~Client(void)
{
	_ofs.close();
	delete _network;
}

Client				&Client::operator=(Client const &rhs)
{
	if (this != &rhs)
		_network = new Network(*(rhs._network));
	return *this;
}

bool				Client::loop(void)
{
	std::string msg;

	_loadServerInfos(_sendTeamInfo());
	while (strtol(_network->send("connect_nbr").c_str(), NULL, 10))
	{
		printDebug("FORKSTEM");
		_forkstem();
	}
	while (~0)
	{
		_ia();
		printDebug("Fin de boucle");
	}
	return true;
}

void				Client::printDebug(const std::string &msg, int mode)
{
	std::locale::global(std::locale(""));
	std::time_t t = std::time(NULL);

	char	mbstr[100] = { '\0' };

	std::strftime(mbstr, sizeof(mbstr) - 1, "%T", std::localtime(&t));
	_ofs << "[" << mbstr << "] " << getpid() << " ";
	if (mode == 1)
		_ofs << ">> ";
	else if (mode == 2)
		_ofs << "<< ";
	else
		_ofs << "   ";
	 _ofs << msg << std::endl;
}

void				Client::hasDied(void)
{
	printDebug("Client is dead.");
	_network->close();
	exit(EXIT_SUCCESS);
}

void				Client::recieveBroadcast(const std::string &msg)
{
	//regex parse msg
	//	 message
	//	 case
	//	 content
	(void)msg;
}

void				Client::_ia(void)
{
	bool ok = false;
	if (_compos(_level) != 0 && _inventory["nourriture"] > 4)
	{
		printDebug("Verification du nombre de joueurs");
		if (_search(_level) != 0)
		{
			ActionIncantation	*incantation 	= static_cast<ActionIncantation *>(Action::create(Action::INCANTATION));
			ActionSee			*voir 			= static_cast<ActionSee *>(Action::create(Action::SEE));

			incantation->setFailureIndex(-1);
			_actions.push_back(incantation); //maj de la carte -> remove item used
			_actions.push_back(voir);
			ok = true;
		}
	}
	if (!ok)
		_composFind(_level);
	_actions.push_back(Action::create(Action::INVENTORY));
	_playMove();
}

void				Client::_playMove(void)
{
	int			tmp;
	int			i	= 0;
	size_t		max	= _actions.size();

	while (i >= 0 && static_cast<size_t>(i) < max)
	{
		tmp = _actions.at(static_cast<size_t>(i))->execute(*_network);
		if (tmp == -2)
			break ;
		i = tmp == -1 ? i + 1 : tmp;
	}

	for (auto &a : _actions)
		delete a;
	_actions.clear();
}

int					Client::_search(int level)
{
	if (level == 1)
		return 1;
	if (level == 2 || level == 3)
	{
		if (_map[_playerX][_playerY].has("joueur", 1))
		{
			printDebug("nb de joueur ok");
			return 1;
		}
	}
	if (level == 4 || level == 5)
	{
		if (_map[_playerX][_playerY].has("joueur", 3))
			return 1;
	}
	if (level == 6 || level == 7)
	{
		if (_map[_playerX][_playerY].has("joueur", 5))
			return 1;
	}
	ActionBroadcast	*a = static_cast<ActionBroadcast *>(Action::create(Action::BROADCAST));
	a->setMessage("TRololo");
	_actions.push_back(a);
	return 0;
}

void	Client::_pathFinding(std::pair<size_t, size_t> start, std::pair<size_t, size_t> end)
{
	std::pair<int, int>	mov;

	mov.first = end.first - start.first < _map.getMapX() / 2 ? end.first + start.first : start.first - (_map.getMapX() - end.first);
	mov.second = end.second - start.second < _map.getMapY() / 2 ? end.second + start.second : start.second - (_map.getMapY() - end.second);

	if (mov.first < 0)
	{
		switch (getPlayerOrientation())
		{
			case NORTH:
			_actions.push_back(Action::create(Action::MOVE_LEFT));
			break ;
			case SOUTH:
			_actions.push_back(Action::create(Action::MOVE_RIGHT));
			break ;
			case EAST:
			_actions.push_back(Action::create(Action::MOVE_RIGHT));
			_actions.push_back(Action::create(Action::MOVE_RIGHT));
			break ;
			default:
			break ;
		}
	}
	else if (mov.first > 0)
	{
		switch (getPlayerOrientation())
		{
			case NORTH:
			_actions.push_back(Action::create(Action::MOVE_RIGHT));
			break ;
			case SOUTH:
			_actions.push_back(Action::create(Action::MOVE_LEFT));
			break ;
			case WEST:
			_actions.push_back(Action::create(Action::MOVE_RIGHT));
			_actions.push_back(Action::create(Action::MOVE_RIGHT));
			break ;
			default:
			break ;
		}
	}
	for (int i = 0; i < abs(mov.first); ++i)
		_actions.push_back(Action::create(Action::MOVE_FORWARD));

	if (mov.second < 0)
	{
		switch (getPlayerOrientation())
		{
			case NORTH:
			_actions.push_back(Action::create(Action::MOVE_RIGHT));
			_actions.push_back(Action::create(Action::MOVE_RIGHT));
			break ;
			case WEST:
			_actions.push_back(Action::create(Action::MOVE_LEFT));
			break ;
			case EAST:
			_actions.push_back(Action::create(Action::MOVE_RIGHT));
			break ;
			default:
			break ;
		}
	}
	else if (mov.second > 0)
	{
		switch (getPlayerOrientation())
		{
			case SOUTH:
			_actions.push_back(Action::create(Action::MOVE_RIGHT));
			_actions.push_back(Action::create(Action::MOVE_RIGHT));
			break ;
			case EAST:
			_actions.push_back(Action::create(Action::MOVE_LEFT));
			break ;
			case WEST:
			_actions.push_back(Action::create(Action::MOVE_RIGHT));
			break ;
			default:
			break ;
		}
	}
	for (int i = 0; i < abs(mov.second); ++i)
		_actions.push_back(Action::create(Action::MOVE_FORWARD));
}

size_t Client::getCaseX(int i)
{
	int tmp;

	tmp = _playerX + i;
	if (tmp < 0)
		return _map.getMapX() - tmp;
	else if (tmp >= (int)_map.getMapX())
		return tmp % _map.getMapX();
	return tmp;
}

size_t Client::getCaseY(int i)
{
	int tmp;

	tmp = _playerY + i;
	if (tmp < 0)
		return _map.getMapY() - tmp;
	else if (tmp >= (int)_map.getMapY())
		return tmp % _map.getMapY();
	return tmp;
}

std::pair<size_t, size_t>	Client::getPairCase(int x, int y)
{
	return std::make_pair<size_t, size_t>(getCaseX(x), getCaseY(y));
}

/**  TEST **/

int getTotalCase(int k)
{
	return (2 * k + 1) * (2 * k + 1);
}

int getNbcircle(int n)
{
	int i;

	for (i = 0; getTotalCase(i) <= n; i++)
		;
	return i;
}

int getCirclePos(int n)
{
	int circle = getNbcircle(n);
	return ((8 * circle + (n - getTotalCase(circle)) + 1)) % (8 * circle);
}

void getOffset(int circle, int pos, int XY[2])
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

void Pos(int n, int XY[2])
{
	int circle = getNbcircle(n);
	int pos = getCirclePos(n);

	XY[0] = -circle;
	XY[1] = -circle;
	getOffset(circle, pos, XY);
}

/*** TEST ***/

void				Client::_composFind(int level)
{
	std::map<std::string, size_t>	&compo = _totems[level];

	printDebug("Enter Composfind");

	int i = 1;
	int A[2] = {0, 0};

	while (i < static_cast<int>(_level * 4 * 4))
	{
		Pos(i, A);
		for (auto &kv : compo)
		{
			if ((_map[getCaseX(A[0])][getCaseY(A[1])].has(kv.first, 1)
			{
				_pathFinding(getPairCase(0, 0), getPairCase(A[0], A[1]));
				ActionTake *a = static_cast<ActionTake *>(Action::create(Action::TAKE));
				a->setObject(kv.first);
				_actions.push_back(a);
				return ;
			}
		}
		i++;
	}

	// /* TEST */
	// if (!_map[_playerX][_playerY + 1].isEmpty())
	// {
	// 	for (auto &kv : compo)
	// 	{
	// 		if (_map[_playerX][_playerY + 1].has(kv.first, 1))
	// 		{
	// 			_pathFinding(getPairCase(0, 0), getPairCase(0, 1));
	// 			ActionTake *a = static_cast<ActionTake *>(Action::create(Action::TAKE));
	// 			a->setObject(kv.first);
	// 			_actions.push_back(a);
	// 			return ;
	// 		}
	// 	}
	// }
	// if (!_map[_playerX + 1][_playerY + 1].isEmpty())
	// {
	// 	for (auto &kv : compo)
	// 	{
	// 		if (_map[_playerX + 1][_playerY + 1].has(kv.first, 1))
	// 		{
	// 			_pathFinding(getPairCase(0, 0), getPairCase(1, 1));
	// 			ActionTake *a = static_cast<ActionTake *>(Action::create(Action::TAKE));
	// 			a->setObject(kv.first);
	// 			_actions.push_back(a);
	// 			return ;
	// 		}
	// 	}
	// }
	// if (!_map[_playerX + 1][_playerY].isEmpty())
	// {
	// 	for (auto &kv : compo)
	// 	{
	// 		if (_map[_playerX + 1][_playerY].has(kv.first, 1))
	// 		{
	// 			_pathFinding(getPairCase(0, 0), getPairCase(1, 0));
	// 			ActionTake *a = static_cast<ActionTake *>(Action::create(Action::TAKE));
	// 			a->setObject(kv.first);
	// 			_actions.push_back(a);
	// 			return ;
	// 		}
	// 	}
	// }
	// if (!_map[_playerX + 1][_playerY - 1].isEmpty())
	// {
	// 	for (auto &kv : compo)
	// 	{
	// 		if (_map[_playerX + 1][_playerY - 1].has(kv.first, 1))
	// 		{
	// 			_pathFinding(getPairCase(0, 0), getPairCase(1, -1));
	// 			ActionTake *a = static_cast<ActionTake *>(Action::create(Action::TAKE));
	// 			a->setObject(kv.first);
	// 			_actions.push_back(a);
	// 			return ;
	// 		}
	// 	}
	// }
	// if (!_map[_playerX][_playerY - 1].isEmpty())
	// {
	// 	for (auto &kv : compo)
	// 	{
	// 		if (_map[_playerX][_playerY - 1].has(kv.first, 1))
	// 		{
	// 			_pathFinding(getPairCase(0, 0), getPairCase(0, -1));
	// 			ActionTake *a = static_cast<ActionTake *>(Action::create(Action::TAKE));
	// 			a->setObject(kv.first);
	// 			_actions.push_back(a);
	// 			return ;
	// 		}
	// 	}
	// }
	// if (!_map[_playerX - 1][_playerY - 1].isEmpty())
	// {
	// 	for (auto &kv : compo)
	// 	{
	// 		if (_map[_playerX - 1][_playerY - 1].has(kv.first, 1))
	// 		{
	// 			_pathFinding(getPairCase(0, 0), getPairCase(-1, -1));
	// 			ActionTake *a = static_cast<ActionTake *>(Action::create(Action::TAKE));
	// 			a->setObject(kv.first);
	// 			_actions.push_back(a);
	// 			return ;
	// 		}
	// 	}
	// }
	// if (!_map[_playerX - 1][_playerY].isEmpty())
	// {
	// 	for (auto &kv : compo)
	// 	{
	// 		if (_map[_playerX - 1][_playerY].has(kv.first, 1))
	// 		{
	// 			_pathFinding(getPairCase(0, 0), getPairCase(-1, 0));
	// 			ActionTake *a = static_cast<ActionTake *>(Action::create(Action::TAKE));
	// 			a->setObject(kv.first);
	// 			_actions.push_back(a);
	// 			return ;
	// 		}
	// 	}
	// }
	// if (!_map[_playerX - 1][_playerY + 1].isEmpty())
	// {
	// 	for (auto &kv : compo)
	// 	{
	// 		if (_map[_playerX - 1][_playerY + 1].has(kv.first, 1))
	// 		{
	// 			_pathFinding(getPairCase(0, 0), getPairCase(-1, 1));
	// 			ActionTake *a = static_cast<ActionTake *>(Action::create(Action::TAKE));
	// 			a->setObject(kv.first);
	// 			_actions.push_back(a);
	// 			return ;
	// 		}
	// 	}
	// }
}

int					Client::_compos(int level)
{
	std::map<std::string, size_t>	&compo = _totems[level];
	bool							ok = false;

	printDebug(_map[_playerX][_playerY].toString());
	if (!_map[_playerX][_playerY].isEmpty()) // check si la case n'est pas trop vielle
	{
		for (auto &kv : compo)
		{
			printDebug("Check de la case pour " + kv.first);
			if (_map[_playerX][_playerY].has(kv.first, kv.second))
			{
				printDebug(std::to_string(kv.second) + " " + kv.first + " trouve sur la case");
				ok = true;
			}
			else
			{
				ok = false;
				break ;
			}
		}
	}
	if (!ok)
	{
		for (auto &kv : compo)
		{
			printDebug("Check inventaire pour " + kv.first);
			if (_inventory.has(kv.first, kv.second))
			{
				ActionDrop	*a = static_cast<ActionDrop *>(Action::create(Action::DROP));
				a->setObject(kv.first);
				_actions.push_back(a);
			}
			else
			{
				ok = false;
				break ;
			}
		}
	}
	if (!ok || _map[_playerX][_playerY].isEmpty()) // add check if pas bouger // case deja connu
	{
		_actions.push_back(Action::create(Action::SEE));
		return 0;
	}
	if (ok)
		return 1;
	return 0;
}

void				Client::_forkstem(void)
{
	pid_t		pid = fork();

	if (pid == 0)
	{
		_network->close();
		Client	c(_network->getPort(), _teamName, _network->getHostName());
		c.loop();
	}
	else if (pid > 0)
		return ;
	else
	{
		_ofs << E_FORK << std::endl;
		exit(EXIT_FAILURE);
	}
}

void				Client::_loadServerInfos(const std::string &infos)
{
	std::smatch	sm;
	std::string	tmp;
	size_t		mapX;
	size_t		mapY;

	try {
		_availableConnections = std::stol(infos);
	} catch (const std::invalid_argument &ia) {
		printDebug(E_UNUSUAL_SERVER_BEHAVIOR);
		exit(EXIT_FAILURE);
	}

	tmp = _network->recieve();
	std::regex_match(tmp, sm, _serverInfosFormat);
	if (sm.size() != 3)
	{
		printDebug(E_UNUSUAL_SERVER_BEHAVIOR);
		exit(EXIT_FAILURE);
	}
	mapX = strtol(sm[1].str().c_str(), NULL, 10);
	mapY = strtol(sm[2].str().c_str(), NULL, 10);
	_map.initMap(mapX, mapY);
}

std::string    		Client::_sendTeamInfo(void)
{
	std::string     msg(_network->recieve());

	if (msg == Network::MSG_WELCOME)
		return _network->send(_teamName);
	else
	{
		printDebug(E_UNUSUAL_SERVER_BEHAVIOR);
		exit(EXIT_FAILURE);
	}
}

void				Client::setPlayerX(int val)
{
	if (val >= static_cast<int>(_map.getMapX()))
		_playerX = val % static_cast<int>(_map.getMapX());
	else if (val < 0)
		_playerX = _map.getMapX() + val;
	else
		_playerX = val;
}

void				Client::setPlayerY(int val)
{
	if (val >= static_cast<int>(_map.getMapY()))
		_playerY = val % static_cast<int>(_map.getMapY());
	else if (val < 0)
		_playerY = _map.getMapY() + val;
	else
		_playerY = val;
}

void				Client::setLevel(unsigned int val) 	{ _level = val; }
void				Client::setPlayerOrientation(enum eOrientation o) 	{ _playerOrientation = o; }
enum eOrientation	Client::getPlayerOrientation() const { return _playerOrientation; }
size_t				Client::getPlayerX() const 			{ return _playerX; }
size_t				Client::getPlayerY() const 			{ return _playerY; }
unsigned int		Client::getLevel() const 			{ return _level; }
Inventory			&Client::getInventory(void) 		{ return _inventory; }
Map					&Client::getMap(void) 				{ return _map; }
Totems				&Client::getTotems() 				{ return _totems; }
