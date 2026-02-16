#include "NickCommand.hpp"
#include "Reply.hpp"

// Parameters: <nickname>
// Numeric Replies:
// 
//     ERR_NONICKNAMEGIVEN = no nickname given             ERR_ERRONEUSNICKNAME = nickname errone avec des char qui ne sont pas valides
//     ERR_NICKNAMEINUSE = nick in use.

NickCommand::NickCommand(std::vector<std::string>& params): ACommand(params) {}

bool	NickCommand::isValidNickname(Client& target, mapClients& ClientArray, t_replyHandler& replyHandler)
{
	if (_commandArray.size() == 1 || _commandArray[1].size() == 0)
	{
		replyHandler.add(target.getFd(), ERR::NONICKNAMEGIVEN(target));
		return false;
	}
	
	if (_commandArray.size() != 2 || _commandArray[1].size() > 9)
	{
		replyHandler.add(target.getFd(), ERR::ERRONEUSNICKNAME(target, _commandArray[1]));
		return false;
	}

	std::string	nickname = _commandArray[1];

	for (std::map<int, Client*>::iterator it = ClientArray.begin(); it != ClientArray.end(); it++)
	{
		if (nickname == it->second->getNickname())
		{
			replyHandler.add(target.getFd(), ERR::NICKNAMEINUSE(target, nickname));
			return false;
		}
	}

	for (size_t i = 0; i < _commandArray.size(); i++)
	{
		if ((i == 0 && !std::isalpha(nickname[i])
					&& !isSpecialChar(nickname[i]))
				&& (!std::isalnum(nickname[i])
					&& !isSpecialChar(nickname[i])
					&& nickname[i] != '-'))
		{
			replyHandler.add(target.getFd(), ERR::ERRONEUSNICKNAME(target, nickname));
			return false;
		}
	}
	return true;
}

t_replyHandler	NickCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ChannelArray;
	t_replyHandler	replyHandler;

	if (!target.getIsRegistered())
	{
		replyHandler.add(target.getFd(), ERR::NOTREGISTERED(target));
		return replyHandler;
	}

	if (!isValidNickname(target, ClientArray, replyHandler))
		return replyHandler;

	target.setNickname(_commandArray[1]);
	replyHandler.add(target.getFd(), RPL::NICK(target));

	return replyHandler;
}

