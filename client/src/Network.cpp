//               .-'''''-.
//             .'         `.
//            :             :        File       : Network.cpp
//           :               :       Creation   : 2015-05-21 01:08:12
//           :      _/|      :       Last Edit  : 2015-07-27 00:17:09
//            :   =/_/      :        Author     : nsierra-
//             `._/ |     .'         Mail       : nsierra-@student.42.fr
//          (   /  ,|...-'
//           \_/^\/||__
//        _/~  `""~`"` \_
//     __/  -'/  `-._ `\_\__
//   /jgs  /-'`  `\   \  \-

#include "Network.hpp"
#include "ErrorMsg.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <strings.h>
#include <string.h>
#include <sys/socket.h>

const size_t		Network::BUFF_SIZE = 32876;
const std::string	Network::MSG_SUCCESS = "ok";
const std::string	Network::MSG_FAILURE = "ko";
const std::string	Network::MSG_DEATH = "mort";
const std::string	Network::MSG_BROADCAST = "message ";
const std::string	Network::MSG_ELEVATION = "elevation en cours";
const std::string	Network::MSG_CURRENT_LVL = "niveau actuel : ";
const std::string	Network::MSG_EXPUSLE = "deplacement";
const std::string	Network::MSG_WELCOME = "BIENVENUE";

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static char	*ft_strnew(size_t size)
{
	char	*str_new;

	str_new = static_cast<char *>(malloc(sizeof(str_new) * size + 1));
	if (str_new)
	{
		bzero(str_new, size);
		return (str_new);
	}
	else
		return (NULL);
}

static char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	total_size;
	char	*str_new;

	if (!s1 || !s2)
		return NULL;
	total_size = strlen(s1) + strlen(s2) + 1;
	str_new = static_cast<char *>(malloc(sizeof(char *) * total_size));
	if (str_new && s1 && s2)
	{
		if (*s1 == '\0' && *s2 == '\0' && !(*str_new = '\0'))
			return (str_new);
		strcpy(str_new, s1);
		strlcat(str_new, s2, total_size);
		return (str_new);
	}
	else
		return (NULL);
}

static void				push_buf(char **remaining, char *buf)
{
	char				*tmp;

	tmp = *remaining;
	*remaining = ft_strjoin(*remaining, buf);
	free(tmp);
}

static void				load_line(char **line, char **remaining, char *found)
{
	char				*tmp;

	*line = strdup(*remaining);
	if (found)
	{
		tmp = *remaining;
		*remaining = strdup(found + 1);
		free(tmp);
	}
	else
		*remaining = NULL;
}

static int				find_newline(char **line, char **remaining)
{
	char				*found;

	if (*remaining && (found = strchr(*remaining, '\n')))
	{
		*found = '\0';
		load_line(line, remaining, found);
		return (1);
	}
	return (0);
}

static int				get_next_line(int const fd, char **line)
{
	static char			*remaining = NULL;
	char				buf[Network::BUFF_SIZE + 1];
	int					read_status;

	if (fd < 1 || !line)
		return (-1);
	bzero(buf, Network::BUFF_SIZE + 1);
	if (find_newline(line, &remaining))
		return (1);
	else if ((read_status = recv(fd, buf, Network::BUFF_SIZE - 1, 0)) <= 0)
	{
		if (remaining && strlen(remaining) > 0)
			load_line(line, &remaining, NULL);
		return (read_status);
	}
	else if (!remaining)
		remaining = ft_strnew(0);
	push_buf(&remaining, buf);
	return (get_next_line(fd, line));
}

Network::Network(Client *client, unsigned int port, std::string hostName) :
	_client(client),
	_hostName(hostName),
	_port(port),
	_connected(false)
{
	_connect();
	if (_connected)
		std::cout << getpid() << " dit " << "Connected to server." << std::endl;
}

Network::Network(Network const & src) :
	_client(src._client)
{
	*this = src;
}

Network::~Network(void)
{
	this->close();
}

Network	&Network::operator=(Network const & rhs)
{
	if (this != &rhs)
	{
		_hostName = rhs._hostName;
		_port = rhs._port;
		_connected = rhs._connected;
		_socket_connect = rhs._socket_connect;
		_sockaddr_connect = rhs._sockaddr_connect;
		_sockaddr_len = rhs._sockaddr_len;
	}
	return *this;
}

void	Network::_initConnection(void)
{
	if ((_socket_connect = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << E_SOCKET_CREATION << std::endl;
		return ;
	}
	_sockaddr_connect.sin_family = AF_INET;
    _sockaddr_connect.sin_port = htons(_port);
	_sockaddr_connect.sin_addr.s_addr = inet_addr(_hostName.c_str());
	bzero(&(_sockaddr_connect.sin_zero), 8);
	_sockaddr_len = sizeof(_sockaddr_connect);


//debug
	// if ((_Debug_socket_connect = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	// {
	// 	std::cout << E_SOCKET_CREATION << std::endl;
	// 	return ;
	// }
	// _Debug_sockaddr_connect.sin_family = AF_INET;
 //    _Debug_sockaddr_connect.sin_port = htons(4244);
	// _Debug_sockaddr_connect.sin_addr.s_addr = inet_addr("10.11.12.9     ");
	// bzero(&(_Debug_sockaddr_connect.sin_zero), 8);
	// _Debug_sockaddr_len = sizeof(_Debug_sockaddr_connect);
}

void	Network::_connect(void)
{
	_initConnection();
	if (connect(_socket_connect, (struct sockaddr *)&_sockaddr_connect, _sockaddr_len) < 0)
		std::cout << E_SOCKET_CONNECTION << std::endl;
	else
		_connected = true;
// //Debug
// 	if (connect(_Debug_socket_connect, (struct sockaddr *)&_Debug_sockaddr_connect, _Debug_sockaddr_len) < 0)
// 		std::cout << E_SOCKET_CONNECTION << std::endl;
}

void	Network::close(void)
{
	if (_connected)
		::close(_socket_connect);
	_connected = false;
}

std::string		Network::recieve(void)
{
	int			ret;
	char		*buf;

	ret = get_next_line(_socket_connect, &buf);
	switch (ret)
	{
		case -1:
			std::cout  << strerror(errno) << std::endl;
			break ;
		case 0:
			this->close();
			break ;
		default:
			_client->printDebug(buf, 2);

			if (!strncmp(buf, MSG_DEATH.c_str(), 5))
				_client->hasDied();
			else if (!strncmp(buf, MSG_BROADCAST.c_str(), 7))
			{
				_client->recieveBroadcast(buf);
				_client->printDebug("Broadcast recieved ! Recieving again...");
				return recieve();
			}
			else if (!strcmp(buf, MSG_ELEVATION.c_str()) && _client->_mode != Client::WAIT_MATES)
			{
				_client->printDebug("Ok, styley ! Recieving again...");





				/// MEGA CRADE

				//clean queue
				_client->setLevel(_client->getLevel() + 1);
				//mode normal



				return recieve();
			}
			else if (!strncmp(buf, MSG_EXPUSLE.c_str(), 11))
			{
				_client->printDebug("Recu expulse");




				//parse buf
				//update player x/y




			}
			return buf;
	}
	return MSG_FAILURE;
}

std::string		Network::send(const std::string &message)
{
	if (_connected)
	{
		std::string		toSend = message;

		toSend += "\n";
		_client->printDebug(message, 1);
		if (::send(_socket_connect, toSend.c_str(), toSend.size(), 0) < 0)
		{
			std::cout << strerror(errno) << std::endl;
			return MSG_FAILURE;
		}
		return recieve();
	}
	std::cout
		<< "Couldn't send message \"" << message
		<< "\" ! Not connected." << std::endl
	;
	exit(EXIT_FAILURE);
	return MSG_FAILURE;
}

bool			Network::isConnected(void) { return _connected; }
std::string		Network::getHostName(void) { return _hostName; }
unsigned int	Network::getPort(void) { return _port; }
int				Network::getSocketPid(void) const { return _socket_connect; }
