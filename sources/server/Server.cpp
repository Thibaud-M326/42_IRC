#include "Server.hpp"
#include <iostream>

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
	_client(),
	_clients()
{
	std::cout << "Server constructor called" << std::endl;	
}

Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
}
