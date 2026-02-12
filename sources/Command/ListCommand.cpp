#include "ListCommand.hpp"

ListCommand::ListCommand(std::vector<std::vector<std::string> >& params): ACommand(params) {}

std::string	ListCommand::ExecuteCommand(std::map<int, Client> ClientArray, std::vector<Channel> ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	return ("");
}
