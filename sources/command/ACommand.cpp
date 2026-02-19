#include "ACommand.hpp"
#include "Irc.hpp"

ACommand::ACommand(std::vector<std::string>& params): _commandArray(params) {}

ACommand::~ACommand() {}

bool	ACommand::isSpecialChar(char c) const
{
	for (size_t i = 0; ircMacro::specialCharArray[i]; i++)
	{
		if (c == ircMacro::specialCharArray[i])
			return true;
	}
	return false;
}

Channel*	ACommand::getChannelByName(std::string chanName, mapChannels& ChannelArray) const
{
	for(mapChannels::iterator it = ChannelArray.begin(); it != ChannelArray.end(); it++)
	{
		if (chanName == it->second->getName())	
			return it->second;
	}
	return NULL;
}

Client*	ACommand::findClientByNickName(std::string nickname, mapClients& ClientArray) const
{
	for (mapClients::iterator it = ClientArray.begin(); it != ClientArray.end(); it++)
	{
		if (it->second->getNickname() == nickname)
			return it->second;
	}
	return NULL;
}