#include "Server.hpp"
#include "Exception.hpp"
#include "Client.hpp"
#include <iostream>
#include <errno.h>
#include <unistd.h>

void Server::readClient(int event_index)
{
	int readSize;

	_client_socket_fd = _events[event_index].data.fd;

	while(0 < (readSize = read(_client_socket_fd, _buffer, sizeof(_buffer))))
	{
		findClient();
		_client->appendRawData(_buffer);
	}

	//client disconnected
	if (readSize == 0)
	{
		std::cout << "Client " << _client_socket_fd << " disconnected" << std::endl;
		_clients.erase(_client_socket_fd);
		close(_client_socket_fd);
	}

	if (readSize == -1)
	{
		//packet read entierly
		if (errno == EAGAIN)
		{
			processClient();
		}
		if (errno != EAGAIN)
		{
			close(_client_socket_fd);
			throw ExceptionPerror(ERR_MSG);
		}
	}
}
