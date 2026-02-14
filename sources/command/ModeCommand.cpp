#include "ModeCommand.hpp"

ModeCommand::ModeCommand(std::vector<std::string>& params): ACommand(params) {}

std::vector<std::string>	ModeCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	(void)target;
	return _replyArray;
}
