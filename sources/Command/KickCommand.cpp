#include "JoinCommand.hpp"

JoinCommand::JoinCommand(std::vector<std::string>& params): ACommand(params) {}

std::string	JoinCommand::ExecuteCommand(std::map<int, Client> ClientArray, std::vector<Channel> ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	return ("");
}
