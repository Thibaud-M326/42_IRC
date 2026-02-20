#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include "Client.hpp"
#include "Exception.hpp"
#include "Server.hpp"

int	Server::set_nonblocking(int sockfd)
{
	int flags = fcntl(sockfd, F_GETFL, 0);
	
    if (flags == -1)
		throw ExceptionPerror(ERR_MSG);

    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1)
		throw ExceptionPerror(ERR_MSG);

    return 0;
}

void	Server::addClientToEpoll()
{
	_ev.events = EPOLLIN | EPOLLET;
	_ev.data.fd = _client_socket_fd;

	if (-1 == epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _client_socket_fd, &_ev))
	{
		close(_client_socket_fd);
		throw ExceptionPerror(ERR_MSG);
	}
}

void	Server::addClient()
{
	int IpAdrress = _client_sock_addr.sin_addr.s_addr;

	Client *client = new Client(_client_socket_fd, IpAdrress);

	//faire aveec insert
	_clients[_client_socket_fd] = client;
}

void	Server::acceptConnection()
{
	while (1) 
	{
		_client_socket_fd = accept(_serv_socket_fd, (struct sockaddr *)&_client_sock_addr, &_client_sock_addr_len);

		if (_client_socket_fd == -1)	
		{
			if (errno == EAGAIN)
				break;
			else
				throw ExceptionPerror(ERR_MSG);
		}

		set_nonblocking(_client_socket_fd);
		addClientToEpoll();
		addClient();

		std::cout << "client fd : " << _client_socket_fd << " connected" << std::endl;
	}
}
