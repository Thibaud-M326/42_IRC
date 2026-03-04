#include <unistd.h>
#include "Channel.hpp"
#include "Client.hpp"
#include "Exception.hpp"
#include "CommandFactory.hpp"
#include "Parse.hpp"
#include "Server.hpp"
#include "QuitCommand.hpp"

void	Server::sendToClients(t_replyHandler& replyHandler, ACommand* cmd)
{
	for (std::vector<t_outGoingMessages>::iterator it = replyHandler.messages.begin(); it != replyHandler.messages.end(); it++)
	{
		for (std::vector<int>::iterator fdIndex = it->targets.begin(); fdIndex != it->targets.end(); fdIndex++)
		{
			if (it->reply.size() <= ircMacro::MAX_BYTES)
			{
				if (send(*fdIndex, it->reply.c_str(), it->reply.size(), 0) == -1)
				{
					delete cmd;
					endSafe(ERR_MSG);
				}
				ircDisplay::send(*fdIndex, it->reply.size(), it->reply);
			}
		}
	}
}

void	Server::executeClient(std::string rawCommands)
{
	if (rawCommands.size() > ircMacro::MAX_BYTES)
	{
		_client->clearBuffer();
		return ;
	}
	Parse parse(rawCommands);
	rawCommands.clear();
	std::vector<std::vector<std::string> > commands;
	CommandFactory factory;

	if (_client)
		_client->clearBuffer();
	commands = parse.parseCommand();

	parse.display_vec(commands);
	for (std::vector<std::vector<std::string> >::iterator it = commands.begin(); it != commands.end(); it++)
	{
		ACommand *cmd = factory.createCommand(*it);
		if (cmd && _client)
		{
		 	t_replyHandler	replyHandler = cmd->ExecuteCommand(*_client, _clients, _channelArray);
			sendToClients(replyHandler, cmd);
			if (dynamic_cast<QuitCommand*>(cmd))
			{
				_clients.erase(_client->getFd());
				close(_client->getFd());
				delete _client;
			}
			delete cmd;
		}
	}
	ircDisplay::endRequest();
}

