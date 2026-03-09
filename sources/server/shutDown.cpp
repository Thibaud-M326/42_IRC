#include "Channel.hpp"
#include "Client.hpp"
#include "Exception.hpp"
#include "Server.hpp"
#include <unistd.h>

void	Server::endSafe(const char* err, const char* file, const char* func, int line)
{
	shutDown();
	throw ExceptionPerror(err, file, func, line);
}

void	Server::shutDown()
{
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		close(it->second->getFd());
		delete it->second;
	}
	_clients.clear();
	for (std::map<std::string, Channel*>::iterator it = _channelArray.begin(); it != _channelArray.end(); it++)
	{
		delete it->second;
	}
	if (_epoll_fd >= 0)
		close(_epoll_fd);
	if (_serv_socket_fd >= 0)
		close(_serv_socket_fd);
	if (_client_socket_fd >= 0)
		close(_client_socket_fd);
}

