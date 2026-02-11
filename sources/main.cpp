#include "Server.hpp"
#include <iostream>

int main()
{
	try 
	{
		Server serv("6667", "password");

		serv.init_server_socket();
		serv.init_epoll();
		serv.run();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}