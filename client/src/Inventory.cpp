//               .-'''''-.
//             .'         `.
//            :             :        File       : Inventory.cpp
//           :               :       Creation   : 2015-06-02 18:59:27
//           :      _/|      :       Last Edit  : 2015-07-27 02:19:26
//            :   =/_/      :        Author     : nsierra-
//             `._/ |     .'         Mail       : nsierra-@student.42.fr
//          (   /  ,|...-'
//           \_/^\/||__
//        _/~  `""~`"` \_
//     __/  -'/  `-._ `\_\__
//   /jgs     /-'`  `\   \  \-

#include <sstream>
#include "Inventory.hpp"

const std::string	Inventory::LINEMATE 	= "linemate";
const std::string	Inventory::DERAUMERE 	= "deraumere";
const std::string	Inventory::SIBUR 		= "sibur";
const std::string	Inventory::MENDIANE 	= "mendiane";
const std::string	Inventory::PHIRAS 		= "phiras";
const std::string	Inventory::THYSTAME 	= "thystame";
const std::string	Inventory::FOOD 		= "nourriture";

Inventory::Inventory()
{

}

Inventory::~Inventory()
{

}

Inventory::Inventory(Inventory const & rhs)
{
	*this = rhs;
}

Inventory&	Inventory::operator=(Inventory const & rhs)
{
	if (this != &rhs)
		_data = rhs._data;
	return *this;
}

size_t 		Inventory::operator[](const std::string & obj)
{
	try {
		return _data.at(obj);
	} catch (const std::out_of_range & oor) {
		return 0;
	}
}

std::string	Inventory::toString() const
{
	std::stringstream ss;

	ss << "[";
	for (auto &kv : _data)
		ss << kv.first << " " << kv.second << ", ";
	ss << "]";
	return ss.str();
}

std::ostream	&operator<<(std::ostream &o, Inventory const &i)
{
	o << i.toString();
	return o;
}

void	Inventory::set(const std::string & obj, size_t qty)
{
	_data[obj] = qty;
}

bool	Inventory::has(const std::string & obj, size_t qty)
{
	try {
		return _data.at(obj) >= qty;
	} catch (const std::out_of_range &oor) {
		return false;
	}
}

void	Inventory::add(const std::string & obj, int qty)
{
	size_t	prevQty;

	try {
		prevQty = _data.at(obj);
	} catch (const std::out_of_range &oor) {
		prevQty = 0;
	}

	if (static_cast<int>(prevQty) + static_cast<int>(qty) < 0)
		_data[obj] = 0;
	else
		_data[obj] = prevQty + qty;

	if (_data.at(obj) == 0)
		_data.erase(obj);
}

void	Inventory::clear(void)
{
	if (_data.size() != 0)	_data.clear();
}

bool	Inventory::isEmpty(void) { return _data.empty(); }
