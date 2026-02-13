#include "UserCommand.hpp"

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

void	UserCommand::setReplyArray(Client& target, std::string realName, int index)
{
	if (_replyArray.size() > 1)
		_replyArray.clear();

	std::ostringstream	oss;
	oss << index;

	_replyArray.push_back(RPL::USER(target, realName, oss.str()));
	_replyArray.push_back(ERR::NEEDMOREPARAMS(target, "USER"));
	_replyArray.push_back(ERR::ALREADYREGISTRED(target));
	_replyArray.push_back(ERR::NOTREGISTERED(target));
}

bool	UserCommand::isValidParams()
{
	if (_CommandArray.size() != 5 || _CommandArray[1].size() > 32)
		return false;
	for (size_t i = 0; i < _CommandArray.size(); i++)
	{
		if (!std::isalnum(_CommandArray[1][i])
				&& !isSpecialChar(_CommandArray[1][i]))
				return false;
	}
	return true;
}

std::string	UserCommand::ExecuteCommand(Client& target, std::map<int, Client>& ClientArray, std::vector<Channel>& ChannelArray)
{
	(void)ChannelArray;

	setReplyArray(target, "", 0);
	
	if (!target.getIsRegistered())
		return _replyArray[userNotRegistered];

	if (!isValidParams())
		return _replyArray[userNeedMoreParams];

	if (!target.getUsername().empty())
		return _replyArray[userAlreadyRegistred];

	size_t	i = 0;

	for (std::map<int, Client>::iterator it = ClientArray.begin(); it != ClientArray.end(); it++)
	{
		if (&it->second == &target)
			break ;
		i++;
	}

	target.setUsername(_CommandArray[1]);

	setReplyArray(target, _CommandArray[4], i);

	return _replyArray[ircMacro::SUCCESS];
}

