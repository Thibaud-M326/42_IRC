#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include "Client.hpp"
#include "Exception.hpp"
#include "Server.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int	Server::set_nonblocking(int sockfd)
{
	int flags = fcntl(sockfd, F_GETFL, 0);
	
    if (flags == -1)
		endSafe(ERR_MSG);

    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1)
		endSafe(ERR_MSG);

    return 0;
}

void	Server::addClientToEpoll()
{
	_ev.events = EPOLLIN;
	_ev.data.fd = _client_socket_fd;

	if (-1 == epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _client_socket_fd, &_ev))
		endSafe(ERR_MSG);
}

void	Server::addClient()
{
	char *IpAdrress = inet_ntoa(_client_sock_addr.sin_addr);

	Client *client = new Client(_client_socket_fd, IpAdrress);

	_clients[_client_socket_fd] = client;
}

void	Server::acceptConnection()
{
	_client_socket_fd = accept(_serv_socket_fd, (struct sockaddr *)&_client_sock_addr, &_client_sock_addr_len);

	if (_client_socket_fd == -1)	
		endSafe(ERR_MSG);

	addClientToEpoll();
	addClient();

	ircDisplay::accept(_client_socket_fd);
}
