//               .-'''''-.
//             .'         `.
//            :             :        File       : Client.hpp
//           :               :       Creation   : 2015-05-21 00:43:58
//           :      _/|      :       Last Edit  : 2015-07-28 03:46:25
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
# include "BroadcastInfos.hpp"

class Network;
class Action;
class Pathfinding;

using Totems = std::vector<std::map<std::string, size_t> >;

class	Client
{
public:

	enum eMode {
		NORMAL,
		WAIT_MATES,
		TOWARDS_MATE,
		REUNION,
		FOOD_EMERGENCY,
		EGG
	};

	enum eBroadcastType : int {
		WAIT,
		STOP_WAITING,
		ON_SAME_CASE,
		INCANTATION
	};

	typedef void (Client::* ClientFunction)();
	typedef void (Client::* BroadcastHandler)(BroadcastInfos &);

	using ModesMap = std::map<enum eMode, ClientFunction>;
	using BroadcastHandlerMap = std::map<enum eMode, BroadcastHandler>;

	Client(unsigned int,
			std::string = "Default Team Name",
			std::string = "localhost");
	~Client(void);
	Client(Client const &);
	Client &operator=(Client const &);

	void					recieveBroadcast(const std::string &);
	bool					loop(void);
	void					hasDied(void);
	Inventory				&getInventory(void);
	unsigned int			getLevel() const;
	void					setLevel(unsigned int);
	size_t					getPlayerX() const;
	void					setPlayerX(int);
	size_t					getPlayerY() const;
	void					setPlayerY(int);
	enum eOrientation		getPlayerOrientation() const;
	void					setPlayerOrientation(enum eOrientation);
	void					printDebug(const std::string &, int = 0);
	Map						&getMap(void);
	Totems					&getTotems();

	std::map<size_t, std::string>	fov;
	Map								map;
	std::vector<Action *>			actions;
	void					elevationTest(void);
	void					expluseTest(const char *);

	enum eMode				_mode;
private:
	static const std::regex	_serverInfosFormat;
	static Totems			_totems;
	ModesMap				_modeFun;
	BroadcastHandlerMap		_broadcastHandler;
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
	size_t					_foodThreshold;
	int						_resetAction;
	size_t					_cycleCount;

	// Broadcasting
	bool					_mustMove;
	bool					_following;
	bool					_landed;
	size_t					_matesOnCase;
	int						_totemDirection;
	std::string				_broadcastTarget;
	size_t					_directionTomove;

	// Modes
	void					_normalMode(void);
	void					_waitMatesMode(void);
	void					_towardsMateMode(void);
	void					_reunionMode(void);
	void					_foodEmergencyMode(void);
	void					_changeToMode(enum eMode);
	void					_eggMode(void);

	// Broadcast
	void					_updateWaitingPosition(BroadcastInfos &);
	void					_normalBroadcastHandler(BroadcastInfos &);
	void					_waitMatesBroadcastHandler(BroadcastInfos &);
	void					_towardsMateBroadcastHandler(BroadcastInfos &);
	void					_reunionBroadcastHandler(BroadcastInfos &);
	void					_foodEmergencyBroadcastHandler(BroadcastInfos &);

	// IA
	void					_ia(void);
	bool					_takeFoodIfAny(void);
	bool					_composOk(void);
	bool					_hasEnoughFood(void);
	bool					_enoughMatesToIncant(void);
	bool					_someoneIsWaiting(void);
	size_t					_getPlayersToFind(void);
	void					_moveTowardsWaitingPlayer(void);
	void					_lookFor(int = 0);
	void					_sendBroadcast(enum eBroadcastType);
	void					_clearActionList(void);
	void					_executeActionList(void);
	void					_explore(void);
	void					_dropCompo(void);
	void					_resetFollowSystem(void);

	void					_moveTo(void);
	void					_moveToUpperLeftCorner(void);
	void					_moveToLeft(void);
	void					_moveToLowerLeftCorner(void);
	void					_moveToBehind(void);
	void					_moveToLowerRightCorner(void);
	void					_moveToRight(void);
	void					_moveToUpperRightCorner(void);

	void					_addAction(const std::string &);
	void					_addActionBegin(const std::string &);

	std::string				_sendTeamInfo(void);
	void					_loadServerInfos(const std::string &);
	void					_forkstem(void);
	void					_checkSlot(void);
};

#endif /* CLIENT_HPP */
