#include "Error.hpp"
#include "Reply.hpp"
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

std::string	UserCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ChannelArray;
	
	if (!target.getIsRegistered())
		return ERR::NOTREGISTERED(target);

	if (!isValidParams())
		return ERR::NEEDMOREPARAMS(target, "USER");

	std::string	username(_CommandArray[1]), realname(_CommandArray[4]);

	if (!target.getUsername().empty())
		return ERR::ALREADYREGISTRED(target);

	size_t	index = 0;

	for (std::map<int, Client*>::iterator it = ClientArray.begin(); it != ClientArray.end(); it++)
	{
		if (it->second == &target)
			break ;
		index++;
	}

	target.setUsername(_CommandArray[1]);

	return RPL::USER(target, _CommandArray[4], index);
}

