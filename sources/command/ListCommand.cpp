#include "ListCommand.hpp"

ListCommand::ListCommand(std::vector<std::string>& params): ACommand(params) {}

t_replyHandler	ListCommand::ExecuteCommand(Client& source, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	t_replyHandler	replyHandler;

	replyHandler.add(source.getFd(), "LIST #twilight,#42");

	return replyHandler;
}
