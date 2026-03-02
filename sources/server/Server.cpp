#include <iostream>
#include "Client.hpp"
#include "Channel.hpp"
#include "Server.hpp"

Server::Server(int port, std::string password)
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
	_clients() {}

Server::~Server()
{
}

