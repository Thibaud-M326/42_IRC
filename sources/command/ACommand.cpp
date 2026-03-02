#include "ACommand.hpp"

ACommand::ACommand(std::vector<std::string>& params): _commandArray(params) {}

ACommand::~ACommand() {}

bool	ACommand::isSpecialChar(char c) const
{
	for (size_t i = 0; ircMacro::specialCharArray[i]; i++)
		if (c == ircMacro::specialCharArray[i])
			return true;
	return false;
}

bool	ACommand::isValidChar(char c) const
{
	for (int i = 0; ircMacro::chanCharArray[i]; i++)
		if (c == ircMacro::chanCharArray[i])
			return true;
	return false;
}

std::vector<Client*>	ACommand::buildClientVec(mapClients& ClientArray) const
{
	std::vector<Client*>	res;

	for (mapClients::iterator it = ClientArray.begin(); it != ClientArray.end(); it++)
	{
		res.push_back(it->second);
	}

	return res;
}

bool	ACommand::isOper(Client& target, Channel& source)
{
	std::vector<Client*>	channel = source.getOperators();

	for (std::vector<Client*>::iterator it = channel.begin(); it != channel.end(); it++)
	{
		if (&target == *it)
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

Client*	ACommand::findClientByNickName(std::string nickname, std::vector<Client*> ClientArray) const
{
	for (std::vector<Client*>::iterator it = ClientArray.begin(); it != ClientArray.end(); it++)
	{
		if ((*it)->getNickname() == nickname)
			return *it;
	}
	return NULL;
}

