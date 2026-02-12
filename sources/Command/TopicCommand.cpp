#include "TopicCommand.hpp"

TopicCommand::TopicCommand(std::vector<std::vector<std::string> >& params): ACommand(params) {}

std::string	TopicCommand::ExecuteCommand(std::map<int, Client> ClientArray, std::vector<Channel> ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	return ("");
}
