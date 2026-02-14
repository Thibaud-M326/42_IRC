#include <unistd.h>
#include "Channel.hpp"
#include "Client.hpp"
#include "CommandFactory.hpp"
#include "Parse.hpp"
#include "Server.hpp"

void	Server::executeClient(std::string rawCommands)
{
	Parse parse(rawCommands);
	std::vector<std::vector<std::string> > commands;
	CommandFactory factory;


	commands = parse.parseCommand();
	std::vector<Channel>	chan;

	parse.display_vec(commands);
	for (std::vector<std::vector<std::string> >::iterator it = commands.begin(); it != commands.end(); it++)
	{
		ACommand *cmd = factory.createCommand(*it);
		if (cmd)
		{
			std::string	reply = cmd->ExecuteCommand(*_client, _clients, chan);
			write(_client->getFd(), reply.c_str(), reply.size());
			delete cmd;
		}
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
