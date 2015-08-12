//               .-'''''-.
//             .'         `.
//            :             :        File       : Network.hpp
//           :               :       Creation   : 2015-05-21 01:03:30
//           :      _/|      :       Last Edit  : 2015-06-04 01:12:19
//            :   =/_/      :        Author     : nsierra-
//             `._/ |     .'         Mail       : nsierra-@student.42.fr
//          (   /  ,|...-'
//           \_/^\/||__
//        _/~  `""~`"` \_
//     __/  -'/  `-._ `\_\__
//   /jgs  /-'`  `\   \  \-

#ifndef NETWORK_HPP
# define NETWORK_HPP

# include "Client.hpp"
# include <string>
# include <sys/socket.h>
# include <netinet/in.h>

class 	Client;

class	Network
{
	public:
		Network(Client *, unsigned int, std::string = "localhost");
		~Network(void);
		Network(Network const & src);
		Network &operator=(Network const &);

		static const std::string	MSG_SUCCESS;
		static const std::string	MSG_FAILURE;
		static const std::string	MSG_DEATH;
		static const std::string	MSG_BROADCAST;
		static const std::string	MSG_ELEVATION;
		static const std::string	MSG_CURRENT_LVL;
		static const std::string	MSG_WELCOME;
		static const size_t			BUFF_SIZE;

		bool				isConnected(void);
		std::string			send(const std::string &);
		std::string			recieve(void);
		std::string			getHostName();
		unsigned int		getPort();
		int					getSocketPid(void) const;
		void				close(void);
		// //debug
		// int					_Debug_socket_connect;
		// struct sockaddr_in	_Debug_sockaddr_connect;
		// size_t				_Debug_sockaddr_len;
	private:

		Client				*_client;

		std::string			_hostName;
		unsigned int		_port;
		bool				_connected;
		int					_socket_connect;
		struct sockaddr_in	_sockaddr_connect;
		size_t				_sockaddr_len;
		void				_connect(void);
		void				_initConnection(void);
};

#endif /* NETWORK_HPP */