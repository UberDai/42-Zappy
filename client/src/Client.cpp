//               .-'''''-.
//             .'         `.
//            :             :        File       : Client.cpp
//           :               :       Creation   : 2015-05-21 00:44:59
//           :      _/|      :       Last Edit  : 2015-07-28 04:12:32
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
#include "BroadcastInfos.hpp"
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
	_foodThreshold(3),
	_resetAction(0),
	_cycleCount(0),
	_startWait(0),
	_mustMove(false),
	_following(false),
	_landed(false),
	_matesOnCase(0),
	_totemDirection(-1),
	_broadcastTarget(""),
	_directionTomove(0)
{
	std::stringstream name;
	name << "debug/" << getpid();
	_ofs.open(name.str().c_str());

	_inventory.add(Inventory::FOOD, 10);
	Action::client = this;

	_modeFun[NORMAL] = &Client::_normalMode;
	_modeFun[WAIT_MATES] = &Client::_waitMatesMode;
	_modeFun[TOWARDS_MATE] = &Client::_towardsMateMode;
	_modeFun[REUNION] = &Client::_reunionMode;
	_modeFun[FOOD_EMERGENCY] = &Client::_foodEmergencyMode;
	_modeFun[EGG] = &Client::_eggMode;

	_broadcastHandler[NORMAL] = &Client::_normalBroadcastHandler;
	_broadcastHandler[WAIT_MATES] = &Client::_waitMatesBroadcastHandler;
	_broadcastHandler[TOWARDS_MATE] = &Client::_towardsMateBroadcastHandler;
	_broadcastHandler[REUNION] = &Client::_reunionBroadcastHandler;
	_broadcastHandler[FOOD_EMERGENCY] = &Client::_foodEmergencyBroadcastHandler;
	_broadcastHandler[EGG] = &Client::_eggBroadcastHandler;
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

void					Client::_updateWaitingPosition(BroadcastInfos & infos)
{
	switch (infos.getType())
	{
		case WAIT:
			if ((!_following && std::stol(infos.getExtraArg()) == _level) || (_following && infos.getPid() == _broadcastTarget))
			{
				_following = true;
				_broadcastTarget = infos.getPid();
				_totemDirection = infos.getDirection();
			}
			break ;

		case STOP_WAITING:
			if (_following && infos.getPid() == _broadcastTarget)
				_resetFollowSystem();
			break ;
	}
}

void					Client::_normalBroadcastHandler(BroadcastInfos & infos)
{
	if (infos.getType() == WAIT && _level == std::stol(infos.getExtraArg()))
	{
		printDebug("Waiting broadcast from same level caught, heading towards him (Mode TOWARDS_MATE).");
		_changeToMode(TOWARDS_MATE);
	}
}

void					Client::_waitMatesBroadcastHandler(BroadcastInfos & infos)
{
	switch (infos.getType())
	{
		case ON_SAME_CASE:
			if (std::stol(infos.getExtraArg()) == getpid())
				++_matesOnCase;
			break ;
		case WAIT:
			printDebug("ptdrmdrlol " + infos.getExtraArg() + " " + std::to_string(_level));
			if (std::stol(infos.getExtraArg()) == _level)
			{
				printDebug("HERE");
				_changeToMode(REUNION);
			}
			break;
		case COMMING:
			if (!(std::find(follower.begin(), follower.end(), std::stol(infos.getExtraArg())) != follower.end()))
				follower.push_back(std::stol(infos.getExtraArg()));
	}
}

void					Client::_towardsMateBroadcastHandler(BroadcastInfos & infos)
{
	switch (infos.getType())
	{
		case INCANTATION:
			printDebug("Recieved an incantation broadcast.");
			_resetFollowSystem();
			_resetAction = 1;
			break ;

		case STOP_WAITING:
			_resetFollowSystem();
			break ;

		default: break ;
	}
}

void					Client::_reunionBroadcastHandler(BroadcastInfos & infos)
{
	switch (infos.getType())
	{
		case STOP_WAITING:
			_resetFollowSystem();
			break ;

		default: break ;
	}
}

void					Client::_foodEmergencyBroadcastHandler(BroadcastInfos & infos)
{
	(void)infos;
}

void					Client::_eggBroadcastHandler(BroadcastInfos & infos)
{
	(void)infos;
}

void				Client::_clearActionList(void)
{
	for (auto &a : actions)
		delete a;
	actions.clear();
}

void				Client::_executeActionList(void)
{
	int			tmp;
	int			i	= 0;
	size_t		max	= actions.size();

	while (i >= 0 && static_cast<size_t>(i) < max)
	{
		if (_resetAction)
		{
			_resetAction = 0;
			_clearActionList();
			_addAction(Action::INCANTATION);
			return;
		}
		tmp = actions.at(static_cast<size_t>(i))->execute(*_network);
		if (tmp == -2)
			break ;
		i = tmp == -1 ? i + 1 : tmp;
	}
	_clearActionList();

	if (tmp == -2)
	{
		_addAction(Action::SEE);
		_executeActionList();
	}
}

void				Client::_dropCompo(void)
{
	if (_level == 8)
		return ;
	std::map<std::string, size_t> & compo = _totems[_level];

	printDebug("dropcompos");
	for (auto & kv : compo)
	{
		int toDrop = static_cast<int>(kv.second - map[_playerX][_playerY][kv.first]);

		toDrop = toDrop < 0 ? 0 : toDrop;

		for (int i = 0; i < toDrop; i++)
		{
			printDebug("drop one of " + kv.first);
			ActionDrop	*a = static_cast<ActionDrop *>(Action::create(Action::DROP));
			a->setObject(kv.first);
			actions.push_back(a);
		}
	}
}

void				Client::_resetFollowSystem(void)
{
	_landed = false;
	_following = false;
	_totemDirection = -1;
	_broadcastTarget = "";
}

void				Client::_changeToMode(enum eMode m)
{
	_mode = m;
}

bool				Client::_composOk(void)
{
	if (_level == 8)
		return false;
	std::map<std::string, size_t> &	levelCompo = _totems[_level];

	printDebug("Composok");
	for (auto & kv : levelCompo)
	{
		printDebug("check for " + kv.first);
		if (_inventory[kv.first] < kv.second)
			return false;
	}
	return true;
}

bool				Client::_takeFoodIfAny(void)
{
	size_t			qty = map[_playerX][_playerY][Inventory::FOOD];

	if (qty == 0)
		return false;

	for (size_t i = 0; i < qty; i++)
	{
		ActionTake *a = static_cast<ActionTake *>(Action::create(Action::TAKE));
		a->setObject(Inventory::FOOD);
		actions.push_back(a);
	}
	return true;
}

bool				Client::_hasEnoughFood(void)
{
	return _inventory.has(Inventory::FOOD, _foodThreshold);
}

bool				Client::_enoughMatesToIncant(void)
{
	if (_matesOnCase >= _getPlayersToFind())
		return true;
	return false;
}

bool				Client::_someoneIsWaiting(void)
{
	return _following;
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

void				Client::_moveTowardsWaitingPlayer(void)
{
	printDebug("Totem direction " + std::to_string(_totemDirection));

	printDebug("Moving toward waiting player");
	switch (_totemDirection)
	{
		case 0:
			if (!_landed)
			{
				printDebug("Same case as waiting player. Sending ON_SAME_CASE.");
				_landed = true;
				_sendBroadcast(ON_SAME_CASE);
			}
			printDebug("On same case as waiting player. Doing nothing.");
			return ;
		case 1: 	return _addAction(Action::MOVE_FORWARD);
		case 2: 	return _moveToUpperLeftCorner();
		case 3: 	return _moveToLeft();
		case 4: 	return _moveToLowerLeftCorner();
		case 5: 	return _moveToBehind();
		case 6: 	return _moveToLowerRightCorner();
		case 7: 	return _moveToRight();
		case 8: 	return _moveToUpperRightCorner();
		default: 	printDebug("Wtf"); return ;
	}
}

void				Client::_lookFor(int mode)
{
	std::map<std::string, size_t> food = { { Inventory::FOOD, _foodThreshold } };
	std::map<std::string, size_t> &	compo = mode == 0 ? _totems[_level] : food;
	int XY[2] = {0, 0};

	for (unsigned i = 1; i < (_level * 4 * 4); i++)
	{
		_path->Pos(i, XY);
		for (auto &kv : compo)
		{
			if (map[_path->getCaseX(XY[0])][_path->getCaseY(XY[1])].has(kv.first, 1) && !_inventory.has(kv.first, kv.second))
			{
				_path->pathfinding(_path->getPairCase(0, 0), _path->getPairCase(XY[0], XY[1]));
				ActionTake *a = static_cast<ActionTake *>(Action::create(Action::TAKE));
				a->setObject(kv.first);

				printDebug("Heading towards closest " + kv.first);
				actions.push_back(Action::create(Action::SEE));
				actions.push_back(a);
				return ;
			}
		}
	}
	_explore();
}

void				Client::_explore(void)
{
	static int rot = 0;

	if (rot < 4)
	{
		printDebug("Rotation exploration");
		actions.push_back(Action::create(Action::MOVE_RIGHT));
		actions.push_back(Action::create(Action::SEE));
		rot++;
	}
	else
	{
		printDebug("Forward exploration");
		for (size_t i = 0; i <= _level; i++)
			actions.push_back(Action::create(Action::MOVE_FORWARD));
		actions.push_back(Action::create(Action::SEE));
		rot = 0;
	}
}

void				Client::_sendBroadcast(enum eBroadcastType t)
{
	std::stringstream		msg;
	std::hash<std::string>	hash;
	ActionBroadcast *		a;

	printDebug("IA - Send Broadcast");

	msg
		<< hash(_teamName) << " "
		<< getpid() << " " << std::to_string(static_cast<int>(t))
	;

	if (t == ON_SAME_CASE || t == COMMING)
		msg << " " << _broadcastTarget;
	else if (t == WAIT)
		msg << " " << _level;
	else
		msg << " .";

	a = static_cast<ActionBroadcast *>(Action::create(Action::BROADCAST));
	a->setMessage(msg.str());
	actions.push_back(a);
}

void				Client::_normalMode(void)
{
	printDebug("IA - Normal Mode");

	if (!_hasEnoughFood() && _takeFoodIfAny())
		return ;
	if (_level == 8)
		return ;
	if (_composOk())
	{
		if (_level == 1)
		{
			printDebug("First level, compos OK, drop compos, incantation.");
			_dropCompo();
			return _addAction(Action::INCANTATION);
		}
		printDebug("Compos ok, level 2+, passage en mode reunion");
		return _changeToMode(REUNION);
	}
	_lookFor();
}

void				Client::_waitMatesMode(void)
{
	printDebug("IA - Wait Mates Mode");

	if (!_hasEnoughFood())
	{
		printDebug("Change to mode food emergency");
		_sendBroadcast(STOP_WAITING);
		return _changeToMode(FOOD_EMERGENCY);
	}

	if (_enoughMatesToIncant())
	{
		printDebug("Enough mates to incant");
		_dropCompo();
		_sendBroadcast(INCANTATION);
		_addAction(Action::INCANTATION);
		_sendBroadcast(STOP_WAITING);
		follower.clear();
		_startWait = 0;
		return _changeToMode(NORMAL);
	}
	printDebug("Nothing special.");
	if (_cycleCount % 30 == 0)
		return _sendBroadcast(WAIT);
	if (_startWait + 200 <= _cycleCount && follower.size() == 0)
	{
		_sendBroadcast(STOP_WAITING);
		return _changeToMode(NORMAL);
	}
	return;
}

void				Client::_towardsMateMode(void)
{
	printDebug("IA - Towards Mate Mode");
	_takeFoodIfAny();

	if (_totemDirection == -1)
	{
		printDebug("No one to follow, NORMAL mode on");
		_changeToMode(NORMAL);
	}
	else
		_moveTowardsWaitingPlayer();
}

void				Client::_reunionMode(void)
{
	printDebug("IA - Reunion Mode");
	if (_someoneIsWaiting())
	{
		printDebug("Someone is waiting, change to mode TOWARDS_MATE");
		//send broadcast team pid pid_cible i'm comming
		_sendBroadcast(COMMING);
		return _changeToMode(TOWARDS_MATE);
	}
	printDebug("No one is waiting, change to mode WAIT_MATES");
	_startWait = _cycleCount;
	_changeToMode(WAIT_MATES);
}

void				Client::_eggMode(void)
{
	printDebug("IA - egg Mode");
	_addAction(Action::EGG);
	_executeActionList();
	return _changeToMode(NORMAL);
}

void				Client::_foodEmergencyMode(void)
{
	printDebug("IA - Food Emergency Mode");
	_resetFollowSystem();
	if (_inventory.has(Inventory::FOOD, _foodThreshold + 6))
	{
		printDebug("Enough food, back to normal mode");
		return _changeToMode(NORMAL);
	}
	_lookFor(1);
}


void				Client::_checkSlot(void)
{
	_addAction(Action::INVENTORY);
	if (_cycleCount % 20 == 0)
	{
		while (strtol(_network->send("connect_nbr").c_str(), NULL, 10))
		{
			printDebug("FORKSTEM");
			_forkstem();
		}
	}
	if (_cycleCount % 800 == 0 && _inventory.has(Inventory::FOOD, 15))
		_changeToMode(EGG);
	_cycleCount++;
}

void				Client::_ia(void)
{
	(this->*_modeFun[_mode])();
	_executeActionList();
	_checkSlot();
}

#include <unistd.h>

bool				Client::loop(void)
{
	std::string msg;

	_loadServerInfos(_sendTeamInfo());
	while (~0)
	{
		_ia();
		printDebug("Fin de boucle");
	}
	usleep(1000);
	return true;
}

void				Client::printDebug(const std::string &msg, int mode)
{
	(void)msg;
	(void)mode;
	// std::locale::global(std::locale(""));
	// std::time_t t = std::time(NULL);
	// char	mbstr[100] = { '\0' };
	//
	// std::strftime(mbstr, sizeof(mbstr) - 1, "%T", std::localtime(&t));
	// _ofs << "[" << mbstr << "] " << getpid() << " ";
	// if (mode == 1)
	// 	_ofs << ">> ";
	// else if (mode == 2)
	// 	_ofs << "<< ";
	// else
	// 	_ofs << "   ";
	// _ofs << msg << std::endl;
}

void				Client::hasDied(void)
{
	printDebug("Client is dead.");
	_network->close();
	exit(EXIT_SUCCESS);
}

void				Client::recieveBroadcast(const std::string &broadcast)
{
	BroadcastInfos	infos(this, broadcast, _teamName);

	if (!infos.isValid())
	{
		printDebug(infos.getError());
		return ;
	}
	printDebug("_updateWaitingPosition");
	_updateWaitingPosition(infos);
	printDebug("_broadcastHandler");
	printDebug(std::to_string(_mode));
	(this->*_broadcastHandler[_mode])(infos);
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
	std::smatch		sm;
	std::string		tmp;
	size_t			mapX;
	size_t			mapY;

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

void				Client::_addActionBegin(const std::string &a)
{
	actions.insert(actions.begin(), Action::create(a));
}

void	Client::elevationTest(void)
{
	_clearActionList();
	setLevel(getLevel() + 1);
	_changeToMode(NORMAL);
}

void	Client::expluseTest(const char *str)
{
	int c;


	c = str[13] + 48;
	switch (c)
	{
		case 1:
			_clearActionList();
			setPlayerY(_playerY + 1);
			break;
		case 7:
			_clearActionList();
			setPlayerX(_playerX + 1);
			break;
		case 5:
			_clearActionList();
			setPlayerY(_playerY - 1);
			break;
		case 3:
			_clearActionList();
			setPlayerX(_playerX - 1);
			break;
	}
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
