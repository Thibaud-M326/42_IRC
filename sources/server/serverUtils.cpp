#include "Server.hpp"
#include "Exception.hpp"
#include "Client.hpp"
#include <iostream>
#include <map>

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

