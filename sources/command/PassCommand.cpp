#include "PassCommand.hpp"

// - PASS - used to set a 'connection password'.
// 	The optional password can and MUST be set before any attempt to register
// 	the connection is made.  Currently this requires that user send a
// 	PASS command before sending the NICK/USER combination.
// Parameters: <password>
//  Numeric Replies:
//          ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

PassCommand::PassCommand(std::vector<std::string>& params): ACommand(params) {}

void	PassCommand::setReplyArray(Client& target)
{
	_replyArray.push_back(ERR::NEEDMOREPARAMS(target, "PASS"));
	_replyArray.push_back(ERR::ALREADYREGISTRED(target));
	_replyArray.push_back(ERR::PASSWDMISMATCH(target));
}

std::string	PassCommand::ExecuteCommand(Client& target, std::map<int, Client>& ClientArray, std::vector<Channel>& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	setReplyArray(target);
	if (_CommandArray.size() == 1 || _CommandArray[1].empty())
		return _replyArray[needMoreParams];
	if (target.getIsRegistred())
		return _replyArray[alreadyRegistred];
	if (_CommandArray[1] != ircMacro::PASSWORD)
		return _replyArray[passwdMissmatch];
	target.setIsRegistred();
	return "";
}

