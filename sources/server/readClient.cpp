#include <iostream>
#include <unistd.h>
#include "Client.hpp"
#include "Channel.hpp"
#include "Exception.hpp"
#include "Server.hpp"

void Server::disconnectClient()
{
	std::cout << "[READ] Client disconnected (fd: " << _client_socket_fd << ")" << std::endl;

	findClient();

	mapChannels& channelList = _client->getChannelList();
	for (mapChannels::iterator it = channelList.begin(); it != channelList.end(); ++it)
	{
		it->second->removeOperator(_client);
		it->second->removeClient(_client);
	}
	_client->clearChannel();
	_clients.erase(_client_socket_fd);

	close(_client_socket_fd);
}

void Server::readClient(int event_index)
{
	int readSize;

	_client_socket_fd = _events[event_index].data.fd;

	while (0 < (readSize = recv(_client_socket_fd, _buffer, sizeof(_buffer), 0)))
	{
		findClient();
		_client->appendRawData(_buffer);
		std::memset(_buffer, 0, sizeof(_buffer));
	}

	if (readSize == 0)
		return disconnectClient();

	if (errno == EAGAIN)
	{
		findClient();
		if (_client->processClient())
			executeClient(_client->getBuffer());
	}
	else
		endSafe(ERR_MSG);
}
