#include "Server.hpp"
#include "Exception.hpp"
#include "Client.hpp"

void	Server::printClients()
{
	std::map<int, Client>::iterator it;

	for (it = _clients.begin(); it != _clients.end(); it++)
	{
		std::cout << it->first << " : " << it->second.getFd() << std::endl;
		std::cout << it->first << " : " << it->second.getIpAddress() << std::endl;
	}
}