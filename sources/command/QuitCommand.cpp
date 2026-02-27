#include "QuitCommand.hpp"

QuitCommand::QuitCommand(std::vector<std::string>& params): ACommand(params) {}

t_replyHandler	QuitCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ChannelArray;
	(void)ClientArray;
	t_replyHandler	replyHandler;

	if (_commandArray.size() == 2)
	{
		mapChannels& channelList = target.getChannelList();

		for (mapChannels::iterator it = channelList.begin(); it != channelList.end(); ++it)
		{
			replyHandler.add(it->second->getClientsFd(), RPL::QUIT(target, _commandArray[1]));
		}
		for (mapChannels::iterator it = channelList.begin(); it != channelList.end(); ++it)
		{
			it->second->removeOperator(&target);
			it->second->removeClient(&target);
		}
	}
	else
	{
		mapChannels& channelList = target.getChannelList();

		for (mapChannels::iterator it = channelList.begin(); it != channelList.end(); ++it)
		{
			replyHandler.add(it->second->getClientsFd(), RPL::QUIT(target, ""));
		}
		for (mapChannels::iterator it = channelList.begin(); it != channelList.end(); ++it)
		{
			it->second->removeOperator(&target);
			it->second->removeClient(&target);
		}
	}
	target.clearChannel();

	return replyHandler;
}

