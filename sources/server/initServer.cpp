#include <iostream>
#include "Server.hpp"
#include "Exception.hpp"

void Server::init_server_socket()
{
	_serv_sock_addr.sin_family = AF_INET;
	_serv_sock_addr.sin_port = htons(PORT);
	_serv_sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	_serv_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_serv_socket_fd == -1)
		throw ExceptionPerror(ERR_MSG);

	if (-1 == set_nonblocking(_serv_socket_fd))
		throw ExceptionPerror(ERR_MSG);

	int opt = 1;
	if (-1 == setsockopt(_serv_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
		throw ExceptionPerror(ERR_MSG);

	if (-1 == bind(_serv_socket_fd, (struct sockaddr *)&_serv_sock_addr, _serv_sock_addr_len))
		throw ExceptionPerror(ERR_MSG);

	if (-1 == listen(_serv_socket_fd, 1))
		throw ExceptionPerror(ERR_MSG);

	std::cout << "[INIT] Server socket created and listening on port " << PORT << std::endl;
}

void Server::init_epoll()
{
	_epoll_fd = epoll_create1(0);
	if (_epoll_fd == -1)
		throw ExceptionPerror(ERR_MSG);

	_ev.events = EPOLLIN;
	_ev.data.fd = _serv_socket_fd;

	if (-1 == epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _serv_socket_fd, &_ev))
		throw ExceptionPerror(ERR_MSG);
	
	std::cout << "[EPOLL] Epoll initialized (fd: " << _epoll_fd << ")" << std::endl;
}
