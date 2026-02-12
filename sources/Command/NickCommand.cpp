#include "NickCommand.hpp"

NickCommand::NickCommand(std::vector<std::vector<std::string> >& params): ACommand(params) {}

std::string	NickCommand::ExecuteCommand(std::map<int, Client> ClientArray, std::vector<Channel> ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	return ("");
}
