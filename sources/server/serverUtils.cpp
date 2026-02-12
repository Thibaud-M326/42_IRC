#include "Server.hpp"
#include "Exception.hpp"
#include "Client.hpp"
#include <iostream>
#include <map>

void	Server::printClients()
{
	std::map<int, Client>::iterator it;

	for (it = _clients.begin(); it != _clients.end(); it++)
	{
		std::cout << it->first << " : " << it->second.getFd() << std::endl;
		std::cout << it->first << " : " << it->second.getIpAddress() << std::endl;
	}
}