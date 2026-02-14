#include "OperCommand.hpp"

OperCommand::OperCommand(std::vector<std::string>& params): ACommand(params) {}

std::string	OperCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	(void)target;
	return ("");
}
