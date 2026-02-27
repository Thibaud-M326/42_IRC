#include "Reply.hpp"
#include "UserCommand.hpp"
#include <ctime>

// -USER - is used at the beginning of connection to specify the username, hostname and realname of a new user.
//    The `<mode>` parameter should be a numeric, and can be used to
//    automatically set user modes when registering with the server.  This
//    parameter is a bitmask, with only 2 bits having any signification: if
//    the bit 2 is set, the user mode 'w' will be set and if the bit 3 is
//    set, the user mode 'i' will be set.  (See Section 3.1.5 "User
//    Modes").
// 
//    The `<realname>` may contain space characters.
// 
//    Parameters: <user> <realname>
//   Numeric Replies:
//
//           ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED


UserCommand::UserCommand(std::vector<std::string>& params): ACommand(params) {}

std::string	UserCommand::getDate()
{
	std::ostringstream	oss;
    std::time_t now = std::time(NULL);
    std::tm* local = std::localtime(&now);

	oss << (local->tm_year + 1900) << "-"
		<< (local->tm_mon + 1) << "-"
		<< local->tm_mday;
	return oss.str();
}

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
	replyHandler.add(target.getFd(), RPL::CREATED(target, getDate()));
	replyHandler.add(target.getFd(), RPL::MYINFO(target));

	return replyHandler;
}

