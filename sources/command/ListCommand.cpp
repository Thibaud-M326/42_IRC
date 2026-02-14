#include "ListCommand.hpp"

ListCommand::ListCommand(std::vector<std::string>& params): ACommand(params) {}

std::string	ListCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	return ("");
}
