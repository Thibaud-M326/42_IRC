#include "Server.hpp"
#include "Client.hpp"
#include <iostream>

void	Server::printClients()
{
	std::cout << "[CLIENTS] Total connected: " << _clients.size() << std::endl;
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		std::cout << "  - fd: " << it->second->getFd() << " | ip: " << it->second->getIpAddress() << std::endl;
	}
}

void	Server::findClient()
{
	_client = _clients[_client_socket_fd];
}

