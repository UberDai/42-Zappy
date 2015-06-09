//               .-'''''-.
//             .'         `.
//            :             :        File       : Map.cpp
//           :               :       Creation   : 2015-06-08 00:57:33
//           :      _/|      :       Last Edit  : 2015-06-09 02:02:50
//            :   =/_/      :        Author     : nsierra-
//             `._/ |     .'         Mail       : nsierra-@student.42.fr
//          (   /  ,|...-'
//           \_/^\/||__
//        _/~  `""~`"` \_
//     __/  -'/  `-._ `\_\__
//   /jgs     /-'`  `\   \  \-

#include <sstream>
#include <regex>
#include "Map.hpp"
#include "Action.hpp"

Map::Map() :
_totox(10),
_totoy(10)
{

}

Map::~Map()
{

}

Map::Map(Map const &rhs)
{
	*this = rhs;
}

Map &	Map::operator=(Map const &rhs)
{
	if (this != &rhs)
		(void)rhs;
	return *this;
}

std::string	Map::toString() const
{
	std::stringstream	ss;

	for (auto & l : _data)
	{
		for (auto & c : l)
			ss << c << " ";
		ss << std::endl;
	}
	return ss.str();
}

std::ostream	&operator<<(std::ostream &o, Map const &i)
{
	o << i.toString();
	return o;
}

Map::Proxy		Map::operator[](size_t index)
{
	return Proxy(_data.at(index));
}

void			Map::initMap(size_t x, size_t y)
{
	_data.clear();
	_data.resize(y);

	for (auto & line : _data)
		line.resize(x);
}

void			Map::setFrom(size_t posX,
	size_t posY,
	enum eOrientation o,
	const std::string & data)
{
	std::regex re("([\\w \\s]*)[,}]");
	std::sregex_iterator next(data.begin(), data.end(), re);
	std::sregex_iterator end;
	std::string	tmp;
	size_t i = 0;

	while (next != end)
	{
		std::smatch match = *next;
		tmp = match.str();
		if (tmp[0] == ' ')
			tmp = match.str().substr(1);
		tmp.resize(tmp.size() - 1);
		//add to map

		std::regex re2("(\\w+)");
		std::sregex_iterator next2(tmp.begin(), tmp.end(), re2);
		std::sregex_iterator end2;
		//clear la case
		while (next2 != end2)
		{
			std::smatch match2 = *next2;
			std::pair<int, int>		coord = _getRealCoord(posX, posY, o, i);
			_data[coord.first][coord.second].add(match2.str(), 1);
			next2++;
		}
		++i;
		next++;
	}
}

std::pair<int, int>				Map::_getRealCoord(size_t x, size_t y, enum eOrientation o, size_t i)
{
	std::pair<int, int>			mapping;
	std::pair<int, int>			XY;
	std::pair<int, int>			ret;
	size_t count = 0;

	mapping.first = 0;
	mapping.second = 0;
	XY.first = 0;
	XY.second = 0;
	switch (o)
	{
		case NORTH:
		mapping.first = 1;
		break ;
		case SOUTH:
		mapping.first = -1;
		break ;
		case EAST:
		mapping.second = 1;
		break ;
		case WEST:
		mapping.second = -1;
		break ;
	}
	while (XY.second <= (int)Action::client->getLevel())
	{
		XY.first = -XY.second;
		while (XY.first <= XY.second)
		{
			if (count == i)
			{
				if (o == NORTH || o == SOUTH)
				{
					ret.first = x + (mapping.first != 0 ? XY.first * mapping.first : XY.first) * mapping.first;
					ret.second = y + (mapping.second != 0 ? XY.second * mapping.second : XY.second) * mapping.first;
				}
				if (o == EAST || o == WEST)
				{
					ret.second  = x - (mapping.first != 0 ? XY.first * mapping.first : XY.first) * mapping.second ;
					ret.first= y - (mapping.second != 0 ? XY.second * mapping.second : XY.second) * mapping.second ;
				}
				if (ret.first < 0)
					ret.first = _totox + ret.first;
				if (ret.second < 0)
					ret.second = _totoy + ret.second;
				if (ret.first >= (int)_totox)
					ret.first = ret.first - _totox;
				if (ret.second >= (int)_totoy)
					ret.second = ret.second - _totoy;
				// std::stringstream toto;
				// toto << "[" << ret.first << " - " << ret.second << " ] - " << i;
				// Action::client->printDebug(toto.str());
				return ret;
			}
			count++;
			XY.first++;
		}
		XY.second++;
	}
	return ret;
}

size_t Map::getMapX() {return _totox; }

size_t Map::getMapY() {return _totoy; }
