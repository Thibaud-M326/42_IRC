#include "Server.hpp"
#include <iostream>
#include "Irc.hpp"

int main()
{
	try 
	{
		Server serv("6667", ircMacro::PASSWORD);

		serv.init_server_socket();
		serv.init_epoll();
		serv.run();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}
