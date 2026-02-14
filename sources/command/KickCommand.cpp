#include "JoinCommand.hpp"

JoinCommand::JoinCommand(std::vector<std::string>& params): ACommand(params) {}

std::string	JoinCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	(void)target;
	return ("");
}
