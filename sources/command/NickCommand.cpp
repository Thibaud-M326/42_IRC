#include "Error.hpp"
#include "NickCommand.hpp"
#include "Reply.hpp"

// Parameters: <nickname>
// Numeric Replies:
// 
//     ERR_NONICKNAMEGIVEN = no nickname given             ERR_ERRONEUSNICKNAME = nickname errone avec des char qui ne sont pas valides
//     ERR_NICKNAMEINUSE = nick in use.

NickCommand::NickCommand(std::vector<std::string>& params): ACommand(params) {}

void	NickCommand::isValidNickname(Client& target, mapClients& ClientArray)
{
	if (_commandArray.size() == 1 || _commandArray[1].size() == 0)
		_replyArray.push_back(ERR::NONICKNAMEGIVEN(target));


	if (_commandArray.size() != 2 || _commandArray[1].size() > 9)
		_replyArray.push_back(ERR::ERRONEUSNICKNAME(target, _commandArray[1]));

	std::string	nickname = _commandArray[1];

	for (std::map<int, Client*>::iterator it = ClientArray.begin(); it != ClientArray.end(); it++)
	{
		if (nickname == it->second->getNickname())
			_replyArray.push_back(ERR::NICKNAMEINUSE(target, nickname));
	}
	for (size_t i = 0; i < _commandArray.size(); i++)
	{
		if ((i == 0 && !std::isalpha(nickname[i])
					&& !isSpecialChar(nickname[i]))
				&& (!std::isalnum(nickname[i])
					&& !isSpecialChar(nickname[i])
					&& nickname[i] != '-'))
				_replyArray.push_back(ERR::ERRONEUSNICKNAME(target, nickname));
	}
}

std::vector<std::string>	NickCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ChannelArray;

	if (!target.getIsRegistered())
		_replyArray.push_back(ERR::NOTREGISTERED(target));

	isValidNickname(target, ClientArray);

	if (_replyArray.empty())
	{
		target.setNickname(_commandArray[1]);
		_replyArray.push_back(RPL::NICK(target));
	}

	return _replyArray;
}

