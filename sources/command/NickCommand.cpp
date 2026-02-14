#include "NickCommand.hpp"

// Parameters: <nickname>
// Numeric Replies:
// 
//     ERR_NONICKNAMEGIVEN = no nickname given             ERR_ERRONEUSNICKNAME = nickname errone avec des char qui ne sont pas valides
//     ERR_NICKNAMEINUSE = nick in use.

NickCommand::NickCommand(std::vector<std::string>& params): ACommand(params) {}

std::string	NickCommand::isValidNickname(Client& target, std::map<int, Client*>& ClientArray)
{
	if (_CommandArray.size() == 1 || _CommandArray[1].size() == 0)
		return ERR::NONICKNAMEGIVEN(target);


	if (_CommandArray.size() != 2 || _CommandArray[1].size() > 9)
		return ERR::ERRONEUSNICKNAME(target, _CommandArray[1]);

	std::string	nickname = _CommandArray[1];

	for (std::map<int, Client*>::iterator it = ClientArray.begin(); it != ClientArray.end(); it++)
	{
		if (nickname == it->second->getNickname())
			return ERR::NICKNAMEINUSE(target, nickname);
	}
	for (size_t i = 0; i < _CommandArray.size(); i++)
	{
		if ((i == 0 && !std::isalpha(nickname[i])
					&& !isSpecialChar(nickname[i]))
				&& (!std::isalnum(nickname[i])
					&& !isSpecialChar(nickname[i])
					&& nickname[i] != '-'))
				return ERR::ERRONEUSNICKNAME(target, nickname);
	}
	return "";
}

std::string	NickCommand::ExecuteCommand(Client& target, std::map<int, Client*>& ClientArray, std::vector<Channel>& ChannelArray)
{
	(void)ChannelArray;

	if (!target.getIsRegistered())
		return ERR::NOTREGISTERED(target);

	std::string	replyCase = isValidNickname(target, ClientArray);

	if (replyCase.empty())
		return replyCase;

	target.setNickname(_CommandArray[1]);

	return (RPL::NICK(target));
}

