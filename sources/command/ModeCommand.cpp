#include "ModeCommand.hpp"

ModeCommand::ModeCommand(std::vector<std::string>& params): ACommand(params) {}

std::string	ModeCommand::ExecuteCommand(Client& target, std::map<int, Client>& ClientArray, std::vector<Channel>& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	return ("");
}
