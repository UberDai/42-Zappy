//               .-'''''-.
//             .'         `.
//            :             :        File       : Map.hpp
//           :               :       Creation   : 2015-06-08 00:57:04
//           :      _/|      :       Last Edit  : 2015-06-09 01:43:04
//            :   =/_/      :        Author     : nsierra-
//             `._/ |     .'         Mail       : nsierra-@student.42.fr
//          (   /  ,|...-'
//           \_/^\/||__
//        _/~  `""~`"` \_
//     __/  -'/  `-._ `\_\__
//   /jgs     /-'`  `\   \  \-

#ifndef MAP_HPP
# define MAP_HPP

# include <string>
# include <iostream>
# include <stdexcept>
# include <vector>
# include "Inventory.hpp"
# include "eOrientation.hpp"

class Inventory;

class Map
{
public:
	Map();
	~Map();
	Map(Map const &);

	std::string	toString() const;
	Map &	operator=(Map const &);

	void			initMap(size_t, size_t);
	void			setFrom(size_t, size_t, enum eOrientation, const std::string &);

	class Proxy {
    public:
        Proxy(std::vector<Inventory> &_array) : _array(_array) { }

        Inventory &operator[](int index) {
            return _array.at(index);
        };
    private:
        std::vector<Inventory> &_array;
    };
	Proxy		operator[](size_t);

private:
	size_t									_totox;
	size_t									_totoy;
	std::vector<std::vector<Inventory> >	_data;
	std::pair<int, int>					_getRealCoord(size_t, size_t, enum eOrientation, size_t);
};

std::ostream	&operator<<(std::ostream &o, Map const &i);

#endif /*MAP_HPP */
