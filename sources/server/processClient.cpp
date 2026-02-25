#include <unistd.h>
#include "Channel.hpp"
#include "Client.hpp"
#include "CommandFactory.hpp"
#include "Parse.hpp"
#include "Server.hpp"
#include "QuitCommand.hpp"

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
		if (cmd && _client)
		{
		 	t_replyHandler	replyHandler = cmd->ExecuteCommand(*_client, _clients, _channelArray);

			for (std::vector<t_outGoingMessages>::iterator it = replyHandler.messages.begin(); it != replyHandler.messages.end(); it++)
			{
				for (std::vector<int>::iterator fdIndex = it->targets.begin(); fdIndex != it->targets.end(); fdIndex++)
				{
					send(*fdIndex, it->reply.c_str(), it->reply.size(), 0);
					std::cout << "[SEND] fd: " << *fdIndex << " | " << it->reply.length() << " bytes\n" << it->reply << std::endl;
				}
			}
			if (dynamic_cast<QuitCommand*>(cmd))
			{
				_clients.erase(_client->getFd());
				delete _client;
			}
			delete cmd;
		}
	}
	std::cout << "================ REQUEST END ================" << std::endl;
}
