#include <iostream>
#include "Client.hpp"
#include "Server.hpp"

Server::Server(std::string port, std::string password)
:
	_port(port),
	_password(password),
	_serv_socket_fd(0),
	_serv_sock_addr(),
	_serv_sock_addr_len(sizeof _serv_sock_addr),
	_epoll_fd(0),
	_events(),
	_ev(),
	_client_socket_fd(0),
	_client_sock_addr(),
	_client_sock_addr_len(sizeof _client_sock_addr),
	_nfds(0),
	_buffer(),
	_client(NULL),
	_clients()
{
	std::cout << "Server constructor called" << std::endl;
}

Server::~Server()
{
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		delete it->second;

	std::cout << "Server destructor called" << std::endl;
}
