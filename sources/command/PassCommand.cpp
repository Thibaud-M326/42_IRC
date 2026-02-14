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

std::string	PassCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	if (_CommandArray.size() == 1 || _CommandArray[1].empty())
		return ERR::NEEDMOREPARAMS(target, "PASS");

	if (target.getIsRegistered())
		return ERR::ALREADYREGISTRED(target);

	if (_CommandArray[1] != ircMacro::PASSWORD)
		return ERR::PASSWDMISMATCH(target);

	target.setIsRegistered();

	return "";
}

