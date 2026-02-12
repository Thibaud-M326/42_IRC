#include "Server.hpp"
#include "Exception.hpp"
#include "Client.hpp"

//trouver le bon client
void	Server::processClient()
{
	_client = _clients[_client_socket_fd];
	_client.appendRawData(_buffer);
}