//               .-'''''-.
//             .'         `.
//            :             :        File       : Client.cpp
//           :               :       Creation   : 2015-05-21 00:44:59
//           :      _/|      :       Last Edit  : 2015-07-22 00:59:16
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
#include <functional>
#include <cctype>

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
	_mode(NORMAL),
	_path(new Pathfinding(*this)),
	_teamName(teamName),
	_network(new Network(this, port, hostName)),
	_level(1),
	_playerX(0),
	_playerY(0),
	_playerOrientation(NORTH),
	_mustMove(false)
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
	delete _path;
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

void				Client::_extractBroadcastInfo(const std::string &b, std::string &msg)
{
	size_t			comaPos = b.find_first_of(',');

	if (comaPos != 9 || !isdigit(b[8]) || b.size() <= 10)
		return printDebug("Broadcast does not seem to be a broadcast");
	msg = b.substr(10);
	_directionTomove = b[8] - 48;
}



void				Client::recieveBroadcast(const std::string &broadcast)
{
	if (_mode != FIND_PLAYER)
		return printDebug("Client is not seeking for player. Broadcast ignored.");
	else if (_mustMove)
		return printDebug("Client is already moving towards another player. Broadcast ignored.");

	std::hash<std::string>	hash;
	std::regex				broadcastFormat("(\\S+) (\\S+) (\\S+)");
	std::smatch				sm;
	std::string				msg;

	_extractBroadcastInfo(broadcast, msg);
	std::regex_match(msg, sm, broadcastFormat);

	if (sm.size() != 4 || std::string(sm[1]) != std::to_string(hash(_teamName)))
		return printDebug("Broadcast recieved is not from our team. Ignoring. size " + std::to_string(sm.size()) + " msg : \"" + msg + "\"");

	// Si tout est ok, poser au sol et envoyer incantation à tout le monde

	if (_broadcastTarget == "")
		_broadcastTarget = std::string(sm[2]);

	if (_directionTomove == 0)
	{
		printDebug("TROUVAY");
		_sendBroadcast(FOUND);
		_mode = WAIT_PLAYER;
		return ;
	}
	_mustMove = true;
}

void						Client::_sendBroadcast(enum eBroadcastType type)
{
	std::stringstream		msg;
	std::hash<std::string>	hash;
	ActionBroadcast			*a;

	msg
		<< hash(_teamName) << " "
		<< getpid() << " "
	;

	if (type == SEEK)
		msg	<< _playersToFind;
	else if (type == FOUND)
		msg << " found " << _broadcastTarget;
	else if (type == ALL_GOOD)
		msg << "incant";

	a = static_cast<ActionBroadcast *>(Action::create(Action::BROADCAST));
	a->setMessage(msg.str());
	actions.push_back(a);
}

void				Client::_setBroadcastMsg(std::stringstream &str)
{
	std::hash<std::string>	hash;

	str
		<< hash(_teamName) << " "
		<< getpid() << " "
		<< _playersToFind
	;
}

void				Client::_findPlayerMode(void)
{
	std::stringstream	msg;

	if (_mustMove)
		return _moveTo();
	_playersToFind = _getPlayersToFind();
	_sendBroadcast(SEEK);
}

void				Client::_ia(void)
{
	bool ok = false;

	if (_mode == FIND_PLAYER && (ok = true))
		_findPlayerMode();
	else if (_compos(_level) != 0 && _inventory["nourriture"] > 4)
	{
		printDebug("Verification du nombre de joueurs");
		if (_search(_level) != 0)
		{
			ActionIncantation	*incantation 	= static_cast<ActionIncantation *>(Action::create(Action::INCANTATION));
			ActionSee			*voir 			= static_cast<ActionSee *>(Action::create(Action::SEE));

			incantation->setFailureIndex(-1);
			actions.push_back(incantation); //maj de la carte -> remove item used
			actions.push_back(voir);
			ok = true;
		}
		else
		{
			printDebug("MODE FIND_PLAYER ON");
			_mode = FIND_PLAYER;
		}
	}
	if (!ok && _mode == NORMAL)
	{
		_composFind(_level);
		actions.push_back(Action::create(Action::INVENTORY));
	}
	_playMove();
}

size_t				Client::_getPlayersToFind(void)
{
	switch (_level)
	{
		case 2: case 3:
			return 2;

		case 4: case 5:
			return 4;

		case 6: case 7:
			return 6;

		default:
			return 4;
	}
}

void				Client::_moveToUpperLeftCorner(void)
{
	_addAction(Action::MOVE_FORWARD);
	_addAction(Action::MOVE_LEFT);
	_addAction(Action::MOVE_FORWARD);
}
void				Client::_moveToLeft(void)
{
	_addAction(Action::MOVE_LEFT);
	_addAction(Action::MOVE_FORWARD);
}
void				Client::_moveToLowerLeftCorner(void)
{
	_addAction(Action::MOVE_LEFT);
	_addAction(Action::MOVE_FORWARD);
	_addAction(Action::MOVE_LEFT);
	_addAction(Action::MOVE_FORWARD);
}
void				Client::_moveToBehind(void)
{
	_addAction(Action::MOVE_LEFT);
	_addAction(Action::MOVE_LEFT);
	_addAction(Action::MOVE_FORWARD);
}
void				Client::_moveToLowerRightCorner(void)
{
	_addAction(Action::MOVE_RIGHT);
	_addAction(Action::MOVE_FORWARD);
	_addAction(Action::MOVE_RIGHT);
	_addAction(Action::MOVE_FORWARD);
}
void				Client::_moveToRight(void)
{
	_addAction(Action::MOVE_RIGHT);
	_addAction(Action::MOVE_FORWARD);
}
void				Client::_moveToUpperRightCorner(void)
{
	_addAction(Action::MOVE_FORWARD);
	_addAction(Action::MOVE_RIGHT);
	_addAction(Action::MOVE_FORWARD);
}

void				Client::_moveTo(void)
{
	_mustMove = false;
	switch (_directionTomove)
	{
		case 1: 	return _addAction(Action::MOVE_FORWARD);
		case 2: 	return _moveToUpperLeftCorner();
		case 3: 	return _moveToLeft();
		case 4: 	return _moveToLowerLeftCorner();
		case 5: 	return _moveToBehind();
		case 6: 	return _moveToLowerRightCorner();
		case 7: 	return _moveToRight();
		case 8: 	return _moveToUpperRightCorner();
		default: 	return;
	}
}

void				Client::_playMove(void)
{
	int			tmp;
	int			i	= 0;
	size_t		max	= actions.size();

	while (i >= 0 && static_cast<size_t>(i) < max)
	{
		tmp = actions.at(static_cast<size_t>(i))->execute(*_network);
		if (tmp == -2)
			break ;
		i = tmp == -1 ? i + 1 : tmp;
	}

	for (auto &a : actions)
		delete a;
	actions.clear();
}

int					Client::_search(int level)
{
	if (level == 1)
		return 1;
	if (level == 2 || level == 3)
	{
		if (map[_playerX][_playerY].has("joueur", 1))
		{
			printDebug("nb de joueur ok");
			return 1;
		}
	}
	if (level == 4 || level == 5)
	{
		if (map[_playerX][_playerY].has("joueur", 3))
			return 1;
	}
	if (level == 6 || level == 7)
	{
		if (map[_playerX][_playerY].has("joueur", 5))
			return 1;
	}
	return 0;
}

void				Client::_composFind(int level)
{
	std::map<std::string, size_t>	&compo = _totems[level];
	int XY[2] = {0, 0};
	static int rot = 0;

	printDebug("Enter Composfind");
	for (int i = 1; i < static_cast<int>((_level * 4 * 4)); i++)
	{
		_path->Pos(i, XY);
		for (auto &kv : compo)
		{
			if (!map[_path->getCaseX(XY[0])][_path->getCaseY(XY[1])].isEmpty() && map[_path->getCaseX(XY[0])][_path->getCaseY(XY[1])].has(kv.first, 1) && !_inventory.has(kv.first, kv.second))
			{
				printDebug("X= " + std::to_string(_path->getCaseX(XY[0])) + " Y= " + std::to_string(_path->getCaseY(XY[1])) );
				printDebug(map[_path->getCaseX(XY[0])][_path->getCaseY(XY[1])].toString());
				printDebug(kv.first + " found on case");
				_path->pathfinding(_path->getPairCase(0, 0), _path->getPairCase(XY[0], XY[1]));
				ActionTake *a = static_cast<ActionTake *>(Action::create(Action::TAKE));
				a->setObject(kv.first);
				if (map[_path->getCaseX(XY[0])][_path->getCaseY(XY[1])].has("nourriture", 1))
				{
					ActionTake *b = static_cast<ActionTake *>(Action::create(Action::TAKE));
					b->setObject("nourriture");
					actions.push_back(b);
				}
				actions.push_back(Action::create(Action::SEE));
				actions.push_back(a);
				return ;
			}
			printDebug(kv.first + " not found on case");
		}
	}
	printDebug(std::to_string(rot));
	if (rot < 4)
	{
		actions.push_back(Action::create(Action::MOVE_RIGHT));
		actions.push_back(Action::create(Action::SEE));
		rot++;
	}
	else
	{
		for (size_t i = 0; i <= _level; i++)
			actions.push_back(Action::create(Action::MOVE_FORWARD));
		actions.push_back(Action::create(Action::SEE));
		rot = 0;
	}
}

int					Client::_compos(int level)
{
	std::map<std::string, size_t>	&compo = _totems[level];
	bool							ok = false;

	printDebug(map[_playerX][_playerY].toString());
	if (!map[_playerX][_playerY].isEmpty())
	{
		for (auto &kv : compo)
		{
			printDebug("Check de la case pour " + kv.first);
			if (map[_playerX][_playerY].has(kv.first, kv.second))
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
				actions.push_back(a);
			}
			else
			{
				ok = false;
				break ;
			}
		}
	}
	if (!ok && map[_playerX][_playerY].isEmpty()) // add check if pas bouger // case deja connu
	{
		actions.push_back(Action::create(Action::SEE));
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
	map.initMap(mapX, mapY);
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
	if (val >= static_cast<int>(map.getMapX()))
		_playerX = val % static_cast<int>(map.getMapX());
	else if (val < 0)
		_playerX = map.getMapX() + val;
	else
		_playerX = val;
}

void				Client::setPlayerY(int val)
{
	if (val >= static_cast<int>(map.getMapY()))
		_playerY = val % static_cast<int>(map.getMapY());
	else if (val < 0)
		_playerY = map.getMapY() + val;
	else
		_playerY = val;
}

void				Client::_addAction(const std::string &a)
{
	actions.push_back(Action::create(a));
}

void				Client::setLevel(unsigned int val) 	{ _level = val; }
void				Client::setPlayerOrientation(enum eOrientation o) 	{ _playerOrientation = o; }
enum eOrientation	Client::getPlayerOrientation() const { return _playerOrientation; }
size_t				Client::getPlayerX() const 			{ return _playerX; }
size_t				Client::getPlayerY() const 			{ return _playerY; }
unsigned int		Client::getLevel() const 			{ return _level; }
Inventory			&Client::getInventory(void) 		{ return _inventory; }
Map					&Client::getMap(void) 				{ return map; }
Totems				&Client::getTotems() 				{ return _totems; }
