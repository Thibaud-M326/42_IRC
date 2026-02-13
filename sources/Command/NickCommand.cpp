#include "NickCommand.hpp"

// Parameters: <nickname>
// Numeric Replies:
// 
//     ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
//     ERR_NICKNAMEINUSE
//     ERR_RESTRICTED

NickCommand::NickCommand(std::vector<std::string>& params): ACommand(params) {}

static int	isValidNickname(std::string nickname)
{

	
	return MacroCommand::SUCCESS;
}

std::string	NickCommand::ExecuteCommand(std::map<int, Client> ClientArray, std::vector<Channel> ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	return ("");
}
