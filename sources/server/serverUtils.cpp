#include "Server.hpp"
#include "Client.hpp"
#include <iostream>

void	Server::printClients()
{
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		std::cout << it->first << " : " << it->second->getFd() << std::endl;
		std::cout << it->first << " : " << it->second->getIpAddress() << std::endl;
	}
}

void	Server::findClient()
{
	_client = _clients[_client_socket_fd];
}

