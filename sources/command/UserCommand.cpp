#include "UserCommand.hpp"
#include <ctime>

UserCommand::UserCommand(std::vector<std::string>& params): ACommand(params) {}

bool	UserCommand::isValidParams()
{
	if (_commandArray.size() != 5 || _commandArray[1].size() > 32)
		return false;
	for (size_t i = 0; i < _commandArray.size(); i++)
	{
		if (!std::isalnum(_commandArray[1][i])
				&& !isSpecialChar(_commandArray[1][i]))
				return false;
	}
	return true;
}

t_replyHandler	UserCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ChannelArray;
	t_replyHandler	replyHandler;
	
	if (!target.getIsConnected() || !target.getISNicknameSet())
	{
		replyHandler.add(target.getFd(), ERR::NOTREGISTERED(target));
		return replyHandler;
	}

	if (target.getIsRegistered())
	{
		replyHandler.add(target.getFd(), ERR::ALREADYREGISTRED(target));
		return replyHandler;
	}

	if (!isValidParams())
	{
		replyHandler.add(target.getFd(), ERR::NEEDMOREPARAMS(target, "USER"));
		return replyHandler;
	}

	std::string	username(_commandArray[1]), realname(_commandArray[4]);

	for (std::map<int, Client*>::iterator it = ClientArray.begin(); it != ClientArray.end(); it++)
	{
		if (it->second == &target)
			break ;
	}

	target.setUsername(_commandArray[1]);
	target.setIsRegistered();
	replyHandler.add(target.getFd(), RPL::WELCOME(target));
	replyHandler.add(target.getFd(), RPL::YOURHOST(target));
	replyHandler.add(target.getFd(), RPL::CREATED(target));
	replyHandler.add(target.getFd(), RPL::MYINFO(target));

	return replyHandler;
}

