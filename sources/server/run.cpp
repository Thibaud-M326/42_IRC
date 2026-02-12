#include "Server.hpp"
#include "Exception.hpp"
#include <sys/epoll.h>

void Server::run()
{
	while (1)
	{
		_nfds = epoll_wait(_epoll_fd, _events, MAX_EVENT, -1);
		if (_nfds == -1)
			throw ExceptionPerror(ERR_MSG);
		
		for (int i = 0; i < _nfds; i++)
		{
			if (_events[i].data.fd == _serv_socket_fd)
				acceptConnection();
			else
				readClient(i);
		}
	}
}
