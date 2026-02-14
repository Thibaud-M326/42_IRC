#include "TopicCommand.hpp"

TopicCommand::TopicCommand(std::vector<std::string>& params): ACommand(params) {}

std::vector<std::string>	TopicCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	(void)target;
	return _replyArray;
}
