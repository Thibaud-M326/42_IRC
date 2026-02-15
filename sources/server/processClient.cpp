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

	parse.display_vec(commands);
	for (std::vector<std::vector<std::string> >::iterator it = commands.begin(); it != commands.end(); it++)
	{
		ACommand *cmd = factory.createCommand(*it);
		if (cmd)
		{
		 	t_replyHandler	replyHandler = cmd->ExecuteCommand(*_client, _clients, _channelArray);
			// BROADCAST
			for (std::vector<t_outGoingMessages>::iterator it = replyHandler.messages.begin(); it != replyHandler.messages.end(); it++)
			{
				for (std::vector<int>::iterator fdIndex = it->targets.begin(); fdIndex != it->targets.end(); fdIndex++)
					write(*fdIndex, it->reply.c_str(), it->reply.size());
			}
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
