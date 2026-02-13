#include "NickCommand.hpp"

// Parameters: <nickname>
// Numeric Replies:
// 
//     ERR_NONICKNAMEGIVEN = no nickname given             ERR_ERRONEUSNICKNAME = nickname errone avec des char qui ne sont pas valides
//     ERR_NICKNAMEINUSE = nick in use.

NickCommand::NickCommand(std::vector<std::string>& params): ACommand(params) {}

unsigned int	NickCommand::isValidNickname(std::map<int, Client>& ClientArray)
{
	if (_CommandArray.size() == 1 || _CommandArray[1].size() == 0)
		return noNickNameGiven;
	for (std::map<int, Client>::iterator it = ClientArray.begin(); it != ClientArray.end(); it++)
	{
		if (_CommandArray[1] == it->second.getNickname())
			return nickNameInUse;
	}
	if (_CommandArray[1].size() > 9)
		return erroneusNickName;
	for (size_t i = 0; i < _CommandArray.size(); i++)
	{
		if ((i == 0 && !std::isalpha(_CommandArray[1][i])
					&& !isSpecialChar(_CommandArray[1][i]))
				&& (!std::isalnum(_CommandArray[1][i])
					&& !isSpecialChar(_CommandArray[1][i])
					&& _CommandArray[1][i] != '-'))
				return erroneusNickName;
	}
	return ircMacro::SUCCESS;
}

void	NickCommand::setReplyArray(Client& target, std::string& badNickname)
{
	_replyArray.push_back(RPL::NICK(target));
	_replyArray.push_back(ERR::NONICKNAMEGIVEN(target));
	_replyArray.push_back(ERR::ERRONEUSNICKNAME(target, badNickname));
	_replyArray.push_back(ERR::NICKNAMEINUSE(target, badNickname));
	_replyArray.push_back(ERR::NOTREGISTERED(target));
}

std::string	NickCommand::ExecuteCommand(Client& target, std::map<int, Client>& ClientArray, std::vector<Channel>& ChannelArray)
{
	(void)ChannelArray;
	setReplyArray(target, _CommandArray[1]);
	if (!target.getIsRegistred())
		return (_replyArray[notRegistered]);

	size_t	replyCase = isValidNickname(ClientArray);

	if (replyCase == ircMacro::SUCCESS)
		target.setNickname(_CommandArray[1]);

	setReplyArray(target, _CommandArray[1]);

	return (_replyArray[replyCase]);
}

