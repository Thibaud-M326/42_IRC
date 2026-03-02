#include <iostream>
#include <vector>
#include "Exception.hpp"
#include "Irc.hpp"
#include "Parse.hpp"
#include "Server.hpp"


std::string	getDate()
{
	std::ostringstream	oss;
	std::time_t now = std::time(NULL);
	std::tm* local = std::localtime(&now);

	oss << (local->tm_year + 1900) << "-"
		<< (local->tm_mon + 1) << "-"
		<< local->tm_mday;
	return oss.str().c_str();
}

namespace ircMacro
{
	std::string	DATE = getDate();
	std::string	PASSWORD;
	int			PORT = 6667;
}

int main(int ac, char *av[])
{
	if (ac == 2 && (!std::strcmp(av[1], "--help")
				|| !std::strcmp(av[1], "-h")))
	{
		ircDisplay::help();
		return 0;
	}
	if (ac != 3 || !verifArgs(av[1], av[2]))
	{
		ircDisplay::usage();
		return 1;
	}
	try
	{
		Server serv(ircMacro::PORT, ircMacro::PASSWORD);

		serv.init_server_socket();
		serv.init_epoll();
		ircDisplay::displayAsciiServ();
		serv.run();
	}
	catch (ExceptionPerror &e)
	{
		std::cerr << ircDisplay::BOLD_RED << e.what() << ircDisplay::STOP_COLOR << std::endl;
	}
	return 0;
}

