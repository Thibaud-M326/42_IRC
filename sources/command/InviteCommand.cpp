#include "InviteCommand.hpp"

InviteCommand::InviteCommand(std::vector<std::string>& params): ACommand(params) {}

std::string	InviteCommand::ExecuteCommand(Client& target, std::map<int, Client*>& ClientArray, std::vector<Channel>& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	return ("");
}
