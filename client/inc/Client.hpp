//               .-'''''-.
//             .'         `.
//            :             :        File       : Client.hpp
//           :               :       Creation   : 2015-05-21 00:43:58
//           :      _/|      :       Last Edit  : 2015-07-22 00:58:30
//            :   =/_/      :        Author     : nsierra-
//             `._/ |     .'         Mail       : nsierra-@student.42.fr
//          (   /  ,|...-'
//           \_/^\/||__
//        _/~  `""~`"` \_
//     __/  -'/  `-._ `\_\__
//   /jgs  /-'`  `\   \  \-

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <map>
# include <regex>
# include <fstream>
# include "Map.hpp"
# include "Network.hpp"
# include "Inventory.hpp"
# include "Action.hpp"
# include "eDirection.hpp"
# include "eOrientation.hpp"
# include "Pathfinding.hpp"

/*
** TODO NOE
**
** - classe IA
*/

class Network;
class Action;
class Pathfinding;

using Totems = std::vector<std::map<std::string, size_t> >;

class	Client
{
public:


	enum eMode {
		NORMAL,
		FIND_PLAYER,
		WAIT_PLAYER
	};

	enum eBroadcastType {
		SEEK,
		FOUND,
		ALL_GOOD
	};

	Client(unsigned int,
			std::string = "Default Team Name",
			std::string = "localhost");
	~Client(void);
	Client(Client const &);
	Client &operator=(Client const &);

	bool					loop(void);
	void					hasDied(void);
	void					recieveBroadcast(const std::string &);
	Inventory				&getInventory(void);
	unsigned int			getLevel() const;
	void					setLevel(unsigned int);
	void					setPlayerX(int);
	size_t					getPlayerY() const;
	void					setPlayerY(int);
	enum eOrientation		getPlayerOrientation() const;
	void					setPlayerOrientation(enum eOrientation);
	Map						&getMap(void);
	size_t					getPlayerX() const;
	Totems					&getTotems();
	void					printDebug(const std::string &, int = 0);

	std::map<size_t, std::string>  fov;
	Map						map;
	std::vector<Action *>	actions;

private:
	static const std::regex	_serverInfosFormat;
	static Totems			_totems;
	enum eMode				_mode;
	Pathfinding				*_path;
	const std::string		_teamName;
	Network					*_network;
	unsigned int			_level;
	unsigned int			_availableConnections;
	std::ofstream 			_ofs;
	Inventory				_inventory;
	size_t					_playerX;
	size_t					_playerY;
	enum eOrientation		_playerOrientation;

	// Broadcasting
	bool					_mustMove;
	std::string				_broadcastTarget;
	size_t					_directionTomove;
	size_t					_playersToFind;
	size_t					_getPlayersToFind(void);
	void					_setBroadcastMsg(std::stringstream &);
	void					_sendBroadcast(enum eBroadcastType type);
	void					_extractBroadcastInfo(const std::string &, std::string &);
	void					_moveTo(void);
	void					_moveToUpperLeftCorner(void);
	void					_moveToLeft(void);
	void					_moveToLowerLeftCorner(void);
	void					_moveToBehind(void);
	void					_moveToLowerRightCorner(void);
	void					_moveToRight(void);
	void					_moveToUpperRightCorner(void);

	void					_addAction(const std::string &);

	std::string				_sendTeamInfo(void);
	void					_loadServerInfos(const std::string &);
	void					_forkstem(void);
	void					_ia(void);
	int						_compos(int);
	void					_composFind(int);
	int						_search(int);
	void					_playMove(void);
	void					_findPlayerMode(void);
};

#endif /* CLIENT_HPP */
