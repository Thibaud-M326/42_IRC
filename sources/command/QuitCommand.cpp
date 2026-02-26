#include "QuitCommand.hpp"

QuitCommand::QuitCommand(std::vector<std::string>& params): ACommand(params) {}

t_replyHandler	QuitCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ChannelArray;
	t_replyHandler	replyHandler;

	if (_commandArray.size() == 2)
	{
		for (mapClients::iterator it = ClientArray.begin(); it != ClientArray.end(); it++)
		{
			replyHandler.add(it->second->getFd(), RPL::QUIT(target, _commandArray[1]));
		}
		for (mapChannels::iterator it = ChannelArray.begin(); it != ChannelArray.end(); it++)
		{
			it->second->removeClient(&target);
		}
	}
	else
	{
		for (mapClients::iterator it = ClientArray.begin(); it != ClientArray.end(); it++)
		{
			replyHandler.add(it->second->getFd(), RPL::QUIT(target, ""));
		}
		for (mapChannels::iterator it = ChannelArray.begin(); it != ChannelArray.end(); it++)
		{
			it->second->removeClient(&target);
		}
	}

	return replyHandler;
}

