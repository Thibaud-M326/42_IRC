#include "Server.hpp"
#include "Exception.hpp"
#include "Client.hpp"
#include "Irc.hpp"
#include "Parse.hpp"
#include <map>

void	Server::executeClient(std::string rawCommands)
{
	Parse parse(rawCommands);
	std::vector<std::vector<std::string> > commands;

	commands = parse.parseCommand();

	std::vector<std::vector<std::string> >::iterator it = commands.begin();

	for (it; it != commands.end(); it++)
	{
		(void)it;
	}
}

void	Server::processClient()
{
	findClient();
	
	std::string clrf = "\r\n";
	std::string clientBuf = _client->getBuffer();
	std::size_t found;
	std::string rawCommands;
	std::string afterLastClrf;

	found = clientBuf.rfind(clrf);
	if (found!=std::string::npos)
	{
		rawCommands = clientBuf.substr(0, found);
		afterLastClrf = clientBuf.substr(found + clrf.length());

		if (afterLastClrf.empty())
			executeClient(rawCommands);
	}
}