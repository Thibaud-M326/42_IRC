#include "ListCommand.hpp"

ListCommand::ListCommand(std::vector<std::string>& params): ACommand(params) {}

t_replyHandler	ListCommand::ExecuteCommand(Client& source, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	t_replyHandler	replyHandler;

	if (_commandArray.size() != 1)
		return replyHandler;

	for (mapChannels::iterator it = ChannelArray.begin(); it != ChannelArray.end(); it++)
	{
		replyHandler.add(source.getFd(), RPL::LIST(*it->second, source, it->second->getClientList().size()));
	}

	replyHandler.add(source.getFd(), RPL::LISTEND(source));

	return replyHandler;
}

