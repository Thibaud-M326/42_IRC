#include "Error.hpp"
#include "PassCommand.hpp"

// - PASS - used to set a 'connection password'.
// 	The optional password can and MUST be set before any attempt to register
// 	the connection is made.  Currently this requires that user send a
// 	PASS command before sending the NICK/USER combination.
// Parameters: <password>
//  Numeric Replies:
//          ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

PassCommand::PassCommand(std::vector<std::string>& params): ACommand(params) {}

std::vector<std::string>	PassCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	if (_commandArray.size() == 1 || _commandArray[1].empty())
		_replyArray.push_back(ERR::NEEDMOREPARAMS(target, "PASS"));

	if (target.getIsRegistered())
		_replyArray.push_back(ERR::ALREADYREGISTRED(target));

	if (_commandArray[1] != ircMacro::PASSWORD)
		_replyArray.push_back(ERR::PASSWDMISMATCH(target));

	if (_replyArray.empty())
		target.setIsRegistered();

	return _replyArray;
}

