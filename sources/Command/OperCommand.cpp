#include "OperCommand.hpp"

OperCommand::OperCommand(std::vector<std::string>& params): ACommand(params) {}

std::string	OperCommand::ExecuteCommand(Client& target, std::map<int, Client>& ClientArray, std::vector<Channel>& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	return ("");
}
