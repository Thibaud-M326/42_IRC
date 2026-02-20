#include <unistd.h>
#include "Channel.hpp"
#include "Client.hpp"
#include "CommandFactory.hpp"
#include "Parse.hpp"
#include "Server.hpp"

#include <iostream>

void	Server::executeClient(std::string rawCommands)
{
	Parse parse(rawCommands);
	rawCommands.clear();
	std::vector<std::vector<std::string> > commands;
	CommandFactory factory;

	_client->clearBuffer();
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
				{
					send(*fdIndex, it->reply.c_str(), it->reply.size(), 0);
					std::cout << "[SEND] fd: " << *fdIndex << " | " << it->reply.length() << " bytes\n" << it->reply << std::endl;
				}
			}
			delete cmd;
		}
	}
	std::cout << "================ REQUEST END ================" << std::endl;
}
