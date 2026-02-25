#include "QuitCommand.hpp"

QuitCommand::QuitCommand(std::vector<std::string>& params): ACommand(params) {}

t_replyHandler	QuitCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ChannelArray;
	(void)target;
	t_replyHandler	replyHandler;

	if (_commandArray.size() == 2)
	{
		for (mapClients::iterator it = ClientArray.begin(); it != ClientArray.end(); it++)
		{
			replyHandler.add(it->second->getFd(), RPL::QUIT(_commandArray[1]));
		}
	}
	else
	{
		for (mapClients::iterator it = ClientArray.begin(); it != ClientArray.end(); it++)
		{
			replyHandler.add(it->second->getFd(), RPL::QUIT(""));
		}
	}

	return replyHandler;
}

