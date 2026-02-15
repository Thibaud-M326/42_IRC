#include "PassCommand.hpp"
#include "Reply.hpp"

// - PASS - used to set a 'connection password'.
// 	The optional password can and MUST be set before any attempt to register
// 	the connection is made.  Currently this requires that user send a
// 	PASS command before sending the NICK/USER combination.
// Parameters: <password>
//  Numeric Replies:
//          ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

PassCommand::PassCommand(std::vector<std::string>& params): ACommand(params) {}

t_replyHandler	PassCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	t_replyHandler	replyHandler;

	if (_commandArray.size() == 1 || _commandArray[1].empty())
	{
		replyHandler.add(target.getFd(), ERR::NEEDMOREPARAMS(target, "PASS"));
		return replyHandler;
	}

	if (target.getIsRegistered())
	{
		replyHandler.add(target.getFd(), ERR::ALREADYREGISTRED(target));
		return replyHandler;
	}

	if (_commandArray[1] != ircMacro::PASSWORD)
	{
		replyHandler.add(target.getFd(),ERR::PASSWDMISMATCH(target));
		return replyHandler;
	}

	target.setIsRegistered();

	return replyHandler;
}

