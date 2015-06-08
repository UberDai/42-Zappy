//               .-'''''-.
//             .'         `.
//            :             :        File       : Map.cpp
//           :               :       Creation   : 2015-06-08 00:57:33
//           :      _/|      :       Last Edit  : 2015-06-08 22:49:25
//            :   =/_/      :        Author     : nsierra-
//             `._/ |     .'         Mail       : nsierra-@student.42.fr
//          (   /  ,|...-'
//           \_/^\/||__
//        _/~  `""~`"` \_
//     __/  -'/  `-._ `\_\__
//   /jgs     /-'`  `\   \  \-

#include <sstream>
#include "Map.hpp"

Map::Map()
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
