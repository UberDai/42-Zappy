//               .-'''''-.
//             .'         `.
//            :             :        File       : main.cpp
//           :               :       Creation   : 2015-05-21 01:45:00
//           :      _/|      :       Last Edit  : 2015-05-22 15:11:54
//            :   =/_/      :        Author     : nsierra-
//             `._/ |     .'         Mail       : nsierra-@student.42.fr
//          (   /  ,|...-'
//           \_/^\/||__
//        _/~  `""~`"` \_
//     __/  -'/  `-._ `\_\__
//   /jgs  /-'`  `\   \  \-

#include "Client.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

bool		retrieveOptions(int ac,
							char * const * av,
							std::string &host,
							std::string &team,
							unsigned int &port)
{
	int		c;
	extern char *optarg;

	opterr = 0;
	while ((c = getopt(ac, av, "n:p:h::")) != -1)
	{
		std::cout << "toto" << std::endl;
		switch (c)
		{
			case 'n':
				team = optarg;
				break ;
			case 'p':
				port = atoi(optarg);
				break ;
			case 'h':
				host = optarg;
				break ;
			case '?':
				if (optopt == 'n')
					std::cout << "Please specify a team name using -n" << std::endl;
				else if (optopt == 'p')
					std::cout << "Please specify a port using -p" << std::endl;
				else
					std::cout << "Unknown option : " << (char)optopt << std::endl;
				return false;
			default:
				abort();
		}
	}
	return true;
}

int			main(int ac, char * const * av)
{
	std::string		host;
	std::string		team;
	unsigned int	port;

	host = "127.0.0.1";
	if (ac < 5)
	{
		std::cout << "Usage: ./client -n <team> -p <port> [-h <hostname>]" << std::endl;
		return 0;
	}
	if (retrieveOptions(ac, av, host, team, port))
	{
		Client	c(port, team, host);
		return c.loop();
	}	
	return 0;
}