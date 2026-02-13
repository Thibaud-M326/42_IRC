#include "Server.hpp"
#include "Exception.hpp"
#include "Client.hpp"
#include <map>

//on envoi la commande que si on a clrf a la fin du raw data et qu'on est a
//la fin de la string
void	Server::processClient()
{
	findClient();
	
	std::string clrf = "\r\n";
	std::string clientBuf = _client->getBuffer();

	std::size_t found = clientBuf.rfind(clrf);

	if (found!=std::string::npos)
		std::cout << 


	std::cout << "_client.getFd() " << _client->getFd() << " _client.getBuffer() : \n" << _client->getBuffer();
}
