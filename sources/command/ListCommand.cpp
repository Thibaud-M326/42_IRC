#include "ListCommand.hpp"

ListCommand::ListCommand(std::vector<std::string>& params): ACommand(params) {}

std::string	ListCommand::ExecuteCommand(Client& target, std::map<int, Client>& ClientArray, std::vector<Channel>& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	return ("");
}
