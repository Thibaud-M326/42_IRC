#include "Server.hpp"

#include <iostream>
#include <sys/epoll.h>

namespace server
{
	const int MAX_EVENT = 10;
}

using server::MAX_EVENT;

//init server value to zero
Server::Server(std::string port, std::string password)
:
	_port(port),
	_password(password),
	_serv_socket(0),
	_client_socket(0),
	_epoll_fd(0),
	_nfds(0),
	_events(),
	_ev(),
	_addr()
{
	std::cout << "Server constructor called" << std::endl;
}

Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
}
