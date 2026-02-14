#include "InviteCommand.hpp"

InviteCommand::InviteCommand(std::vector<std::string>& params): ACommand(params) {}

std::string	InviteCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	(void)target;
	return ("");
}
