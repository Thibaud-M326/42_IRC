#include "Server.hpp"
#include <iostream>
#include "Exception.hpp"
#include "Irc.hpp"
#include "Parse.hpp"
#include <vector>

namespace ircMacro
{
	std::string	PASSWORD;
	int			PORT = 6667;
}

int main(int ac, char *av[])
{
	if (ac == 2 && (!std::strcmp(av[1], "--help")
				|| !std::strcmp(av[1], "-h")))
	{
		std::cout << ircMacro::help() << std::endl;
		return 0;
	}
	if (ac != 3 || !verifArgs(av[1], av[2]))
	{
		std::cerr << ircMacro::BOLD_RED << ircMacro::USAGE << ircMacro::STOP_COLOR << std::endl;
		return 1;
	}
	try
	{
		Server serv(ircMacro::PORT, ircMacro::PASSWORD);

		serv.init_server_socket();
		serv.init_epoll();
		ircMacro::displayAsciiServ();
		serv.run();
	}
	catch (ExceptionPerror &e)
	{
		std::cerr << ircMacro::BOLD_RED << e.what() << ircMacro::STOP_COLOR << std::endl;
	}
	return 0;
}

