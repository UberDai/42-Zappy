//               .-'''''-.
//             .'         `.
//            :             :        File       : BroadcastInfos.hpp
//           :               :       Creation   : 2015-07-28 01:19:20
//           :      _/|      :       Last Edit  : 2015-07-28 02:49:40
//            :   =/_/      :        Author     : nsierra-
//             `._/ |     .'         Mail       : nsierra-@student.42.fr
//          (   /  ,|...-'
//           \_/^\/||__
//        _/~  `""~`"` \_
//     __/  -'/  `-._ `\_\__
//   /        /-'`  `\   \  \-

#ifndef BROADCAST_INFOS
# define BROADCAST_INFOS

# include <string>

class Client;

class BroadcastInfos
{
public:
	BroadcastInfos(Client *, const std::string &, const std::string &);

	bool			isValid(void) const;
	int				getDirection(void) const;
	std::string		getPid(void) const;
	int				getType(void) const;
	std::string		getExtraArg(void) const;
	std::string		getMessage(void) const;
	std::string		getError(void) const;

private:
	Client			*_c;
	int				_status;
	std::string		_original;
	std::string		_teamName;
	int				_direction;
	std::string		_message;
	std::string		_pid;
	std::string		_type;
	std::string		_extraArg;

	void			_getDirAndMessage(void);
	void			_extractBroadcastInfo(void);
};

#endif