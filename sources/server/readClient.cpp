#include <iostream>
#include <unistd.h>
#include "Client.hpp"
#include "Exception.hpp"
#include "Server.hpp"

void Server::readClient(int event_index)
{
	int readSize;

	_client_socket_fd = _events[event_index].data.fd;

	readSize = recv(_client_socket_fd, _buffer, sizeof(_buffer), 0);

	//Client disconected from server
	if (readSize == 0)
	{
		findClient();
		if (_client)
			executeClient("QUIT :Leaving\r\n");
		ircDisplay::readClientDisco(_client_socket_fd);
	}

	if (readSize == -1)
		endSafe(ERR_MSG);

	if (readSize > 0)
	{
		findClient();
		_client->appendRawData(_buffer);
		std::memset(_buffer, 0, sizeof(_buffer));
		if (_client->processClient())
			executeClient(_client->getBuffer());
	}
}

