//               .-'''''-.
//             .'         `.
//            :             :        File       : Client.cpp
//           :               :       Creation   : 2015-05-21 00:44:59
//           :      _/|      :       Last Edit  : 2015-06-04 01:53:50
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

const std::regex	Client::_serverInfosFormat("(\\d+)\\n(\\d+) (\\d+)\\n");

std::vector<std::map<std::string, size_t> >	Client::_totems =
	{
		{
			{  }
		},
		{
			{ Inventory::LINEMATE, 1 }
		},
		{
			{ Inventory::LINEMATE, 1 },
			{ Inventory::DERAUMERE, 1 },\
			{ Inventory::SIBUR, 1 },
		},
		{
			{ Inventory::LINEMATE, 2 },
			{ Inventory::SIBUR, 1 },
			{ Inventory::PHIRAS, 2 },
		},
		{
			{ Inventory::LINEMATE, 1 },
			{ Inventory::DERAUMERE, 1 },
			{ Inventory::SIBUR, 2 },
			{ Inventory::PHIRAS, 1 },
		},
		{
			{ Inventory::LINEMATE, 1 },
			{ Inventory::DERAUMERE, 2 },
			{ Inventory::SIBUR, 1 },
			{ Inventory::MENDIANE, 3 },
		},
		{
			{ Inventory::LINEMATE, 1 },
			{ Inventory::DERAUMERE, 2 },
			{ Inventory::SIBUR, 3 },
			{ Inventory::PHIRAS, 1 },
		},
		{
			{ Inventory::LINEMATE, 2 },
			{ Inventory::DERAUMERE, 2 },
			{ Inventory::SIBUR, 2 },
			{ Inventory::MENDIANE, 2 },
			{ Inventory::PHIRAS, 2 },
			{ Inventory::THYSTAME, 1 },
		},
	}
;


Client::Client(unsigned int port, std::string teamName, std::string hostName) :
	_teamName(teamName),
	_network(new Network(this, port, hostName)),
	_level(1)
{

	std::stringstream name;
	name << "debug/" << getpid();
	_ofs.open(name.str().c_str());

	_inventory.add(Inventory::FOOD, 10);
}

Client::Client(Client const & src) :
_teamName(src._teamName)
{
	*this = src;
}

Client::~Client(void)
{
	_ofs.close();
	delete _network;
}

Client	&Client::operator=(Client const & rhs)
{
	if (this != &rhs)
		_network = new Network(*(rhs._network));
	return *this;
}

IAction					*Client::_createAction(const std::string & action)
{
	if (action == IAction::SEE)
		return new ActionSee(this);
	if (action == IAction::EXPULSE)
		return new ActionExpulse();
	if (action == IAction::INCANTATION)
		return new ActionIncantation(this);
	if (action == IAction::EGG)
		return new ActionEgg();
	return nullptr;
}

IAction					*Client::_createAction(enum eDirection dir)
{
	return new ActionMove(dir);
}

IAction					*Client::_createAction(const std::string & action, const std::string &str)
{
	if (action == IAction::TAKE)
		return new ActionTake(str, _inventory);
	if (action == IAction::DROP)
		return new ActionDrop(str, _inventory);
	if (action == IAction::BROADCAST)
		return new ActionBroadcast(str);
	return nullptr;
}

bool	Client::loop(void)
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
			
			// _network->recieve();
		}
	return true;
}

void	Client::printDebug(const std::string & msg)
{
	std::locale::global(std::locale(""));
    std::time_t t = std::time(NULL);

	char	mbstr[100] = { '\0' };

	std::strftime(mbstr, sizeof(mbstr) - 1, "%T", std::localtime(&t));
	_ofs << "[" << mbstr << "] " << getpid() << " " << msg << std::endl;
}

void	Client::hasDied(void)
{
	printDebug("Client is dead.");
	_network->close();
	exit(EXIT_SUCCESS);
}

void	Client::recieveBroadcast(const std::string & msg)
{
	//regex parse msg
	//	 message
	//	 case
	//	 content
	(void)msg;
		// switch (atoi(case))
		// {
		// 	case 1:
		// 		_move(UP);
		// 		break;
		// 	case 2:
		// 		break;
		// 	case 3:
		// 		break;
		// 	case 4:
		// 		break;
		// 	case 5:
		// 		break;
		// 	case 6:
		// 		break;
		// 	case 7:
		// 		break;
		// 	case 8:
		// 		break;
		// 	default:
		// 		break;
		// }
}

void	Client::_ia(void)
{
		if (_compos(_level) && _inventory["nourriture"] > 4)
		{
			if (_level > 1)
				_search();
			_actions.push_back(_createAction("incantation"));
		}
		else
			_composFind(_level);
		_playMove();
}

void			Client::_playMove(void)
{
	int			tmp;
	int			i	= 0;
	size_t		max	= _actions.size();

	while (i >= 0 && static_cast<size_t>(i) < max)
	{
		// printDebug(std::to_string(i));
		tmp = _actions[static_cast<size_t>(i)]->execute(*_network);

		if (tmp == -2)
			break ;
		i = tmp == -1 ? i + 1 : tmp;
	}

	for (auto &a : _actions)
		delete a;
	_actions.clear();
	// int			tmp;

	// tmp = 0;
	// for (auto &action : _actions)
	// {
	// 	tmp = tmp != -1 ? action->execute(*_network) : -1;
	// 	delete action;
	// }
	// _actions.clear();
}

void			Client::_search(void)
{
	// std::string dir;
	// int 		players;

	// while (players != nb_player)
	// {
	// 	_broadcast("incantation level " + _level + "\n");
	// 	dir = _network->recieve();

	// }
}


void			Client::_composFind(int level)
{
	(void)level;
	//if nourriture take nourriture
	//take compos for all level
}

int				Client::_compos(int level)
{
	std::map<std::string, size_t> &compo = _totems[level];
	bool		ok = true;

	if (fov[0].size())
	{
	 	for (auto &kv : compo)
	 		{
			if (fov[0].find(kv.first))
				ok = true;
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
			if (_inventory.has(kv.first, kv.second))
			{
				_actions.push_back(_createAction(IAction::DROP, kv.first));
			}
			else
			{
				ok = false;
				break ;
			}
		}
	}
	if (!ok)
		_actions.push_back(_createAction(IAction::SEE));
	return (ok == true);
}

void			Client::_forkstem(void)
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

// void					Client::_updateInventory(const std::string &obj, int qty)
// {
// 	_inventory[obj] += qty;
// }

// int						Client::_inInventory(const std::string &name, size_t qty)
// {
// 	return (_inventory[name] >= qty);
// }

// void					Client::_updateInventory(void)
// {
// 	std::string			data;

// 	data = _network->send("inventaire");
// }

void			Client::_loadServerInfos(const std::string &infos)
{
	std::smatch	sm;
	std::string	tmp;

	std::regex_match(infos, sm, _serverInfosFormat);
	if (sm.size() != 4)
	{
		printDebug(E_UNUSUAL_SERVER_BEHAVIOR);
		exit(EXIT_FAILURE);
	}
	tmp = sm[1],  _availableConnections = strtol(tmp.c_str(), NULL, 10);
	tmp = sm[2],  _mapX = strtol(tmp.c_str(), NULL, 10);
	tmp = sm[3],  _mapY = strtol(tmp.c_str(), NULL, 10);
}

std::string    Client::_sendTeamInfo(void)
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

unsigned int	Client::getLevel() const
{
	return _level;
}

void	Client::setLevel(unsigned int val)
{
	_level = val;
}