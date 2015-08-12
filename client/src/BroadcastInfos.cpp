//               .-'''''-.
//             .'         `.
//            :             :        File       : BroadcastInfos.cpp
//           :               :       Creation   : 2015-07-28 01:19:36
//           :      _/|      :       Last Edit  : 2015-07-28 02:50:13
//            :   =/_/      :        Author     : nsierra-
//             `._/ |     .'         Mail       : nsierra-@student.42.fr
//          (   /  ,|...-'
//           \_/^\/||__
//        _/~  `""~`"` \_
//     __/  -'/  `-._ `\_\__
//   /        /-'`  `\   \  \-

#include <iostream>
#include <regex>
#include "BroadcastInfos.hpp"
#include "Client.hpp"

BroadcastInfos::BroadcastInfos(Client *c, const std::string & broadcast, const std::string & teamName) :
	_c(c),
	_status(1),
	_original(broadcast),
	_teamName(teamName),
	_direction(-1),
	_message(""),
	_pid(""),
	_extraArg("")
{
	(void)_c;
	_getDirAndMessage();
	_extractBroadcastInfo();
}

void				BroadcastInfos::_getDirAndMessage(void)
{
	size_t			comaPos = _original.find_first_of(',');

	if (comaPos != 9 || !isdigit(_original[8]) || _original.size() <= 10)
	{
		_status = -1;
		return ;
	}
	_direction = _original[8] - 48;
	_message = _original.substr(10);
}

void				BroadcastInfos::_extractBroadcastInfo(void)
{
	std::hash<std::string>	hash;
	std::regex				broadcastFormat("(\\S+) (\\S+) (\\S+) (\\S+)");
	std::smatch				sm;

	std::regex_match(_message, sm, broadcastFormat);


	if (!(sm.size() > 3 && sm.size() < 6) || std::string(sm[1]) != std::to_string(hash(_teamName)))
	{
		_status = -2;
		return ;
	}
	_pid = std::string(sm[2]);
	_type = std::string(sm[3]);
	_extraArg = sm.size() == 5 ? std::string(sm[4]) : "";
}

std::string		BroadcastInfos::getError(void) const
{
	if (_status == -1)
		return "Broadcast has a weird format.";
	else if (_status == -2)
		return "Broadcast is not from our team.";
	return "";
}

bool			BroadcastInfos::isValid(void) const
{
	return _status == 1;
}
int				BroadcastInfos::getDirection(void) const
{
	if (isValid())
		return _direction;
	return -1;
}

std::string		BroadcastInfos::getPid(void) const
{
	if (isValid())
		return _pid;
	return "";
}

int				BroadcastInfos::getType(void) const
{
	if (isValid())
		return std::stol(_type);
	return -1;
}

std::string		BroadcastInfos::getExtraArg(void) const
{
	if (isValid())
		return _extraArg;
	return "";
}

std::string		BroadcastInfos::getMessage(void) const
{
	if (isValid())
		return _message;
	return "";
}
