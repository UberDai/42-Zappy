//               .-'''''-.
//             .'         `.
//            :             :        File       : Client.cpp
//           :               :       Creation   : 2015-05-21 00:44:59
//           :      _/|      :       Last Edit  : 2015-05-23 03:55:33
//            :   =/_/      :        Author     : nsierra-
//             `._/ |     .'         Mail       : nsierra-@student.42.fr
//          (   /  ,|...-'
//           \_/^\/||__
//        _/~  `""~`"` \_
//     __/  -'/  `-._ `\_\__
//   /jgs  /-'`  `\   \  \-

#include "Client.hpp"
#include "ErrorMsg.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <regex>

const std::regex	Client::_serverInfosFormat("(\\d+)\\n(\\d+) (\\d+)\\n");

Client::Client(unsigned int port, std::string teamName, std::string hostName) :
_teamName(teamName),
_network(new Network(port, hostName))
{
	std::stringstream name;
	name << "debug/" << getpid();
	_ofs.open(name.str().c_str());
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

bool	Client::loop(void)
{
	std::string msg;
	
	_loadServerInfos(_sendTeamInfo());
	while (42)
	{
		if (msg == "mort\n")
			exit(0);
		if (strtol(_network->send("connect_nbr\n").c_str(), NULL, 10))
			_forkstem();
		else 
		{
			msg = _network->recieve();	
			_ofs << getpid() << " recoit " << msg << std::endl;
		}
	}
	return true;
}

void			Client::_forkstem(void)
{
	pid_t		pid = fork();

	if (pid == 0)
	{
		std::stringstream	cmd;

		cmd
			<< "./client -n " << _teamName
			<< " -p " << _network->getPort()
			<< " -h " << _network->getHostName()
		;
		system(cmd.str().c_str());
	}
	else if (pid > 0)
		return ;
	else
	{
		_ofs << E_FORK << std::endl;
		exit(EXIT_FAILURE);
	}
}

void			Client::_loadServerInfos(const std::string &infos)
{
	std::smatch	sm;
	std::string	tmp;

	_ofs << infos << std::endl;
	std::regex_match(infos, sm, _serverInfosFormat);
	if (sm.size() != 4)
	{
		_ofs << E_UNUSUAL_SERVER_BEHAVIOR << std::endl;
		exit(EXIT_FAILURE);
	}
	tmp = sm[1],  _availableConnections = strtol(tmp.c_str(), NULL, 10);
	tmp = sm[2],  _mapX = strtol(tmp.c_str(), NULL, 10);
	tmp = sm[3],  _mapY = strtol(tmp.c_str(), NULL, 10);
}

std::string    Client::_sendTeamInfo(void)
{
	std::string     msg(_network->recieve());

	_ofs << msg << std::endl;
	if (msg == "BIENVENUE\n")
		return _network->send(_teamName + "\n");
	else
	{
		_ofs << E_UNUSUAL_SERVER_BEHAVIOR << std::endl;
		exit(EXIT_FAILURE);
	}
}