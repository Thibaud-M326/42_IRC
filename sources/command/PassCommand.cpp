#include "PassCommand.hpp"

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

	if (target.getIsConnected())
	{
		replyHandler.add(target.getFd(), ERR::ALREADYREGISTRED(target));
		return replyHandler;
	}

	if (_commandArray[1] != ircMacro::PASSWORD)
	{
		replyHandler.add(target.getFd(),ERR::PASSWDMISMATCH(target));
		return replyHandler;
	}

	target.setIsConnected();

	return replyHandler;
}

