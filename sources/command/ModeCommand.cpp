#include "ModeCommand.hpp"
#include "Irc.hpp"

//- MODE - Change the user's mode:
//	A user MODE command MUST only be accepted if both the sender of the
//	message and the nickname given as a parameter are both the same.  If
//	no other parameter is given, then the server will return the current
//	settings for the nick.
//
//Parameters: <nickname> *( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )
//

ModeCommand::ModeCommand(std::vector<std::string>& params): ACommand(params) {}

char	ModeCommand::isValidFlag(char c)
{
	for (size_t i = 0; ircMacro::modeCharArray[i]; i++)
	{
		if (c == ircMacro::modeCharArray[i])
			return c;
	}
	return '\0';
}

char	ModeCommand::verifFlag()
{
	for(size_t i = 2; i < _commandArray.size(); i++)
	{
		for (size_t j = 1; _commandArray[i][j]; j++)
		{
			char c = isValidFlag(_commandArray[i][j]);
			if (c)
				return c;
		}
	}
	return '\0';
}

bool	ModeCommand::isOper(Client& target, Channel& source)
{
	std::vector<Client*>	channel = source.getOperators();

	for (std::vector<Client*>::iterator it = channel.begin(); it != channel.end(); it++)
	{
		if (&target == *it)
			return true;
	}

	return false;
}

//   Numeric Replies:
//
//           ERR_KEYSET
//           ERR_NOCHANMODES                 ERR_CHANOPRIVSNEEDED
//           ERR_USERNOTINCHANNEL            ERR_UNKNOWNMODE
//           RPL_CHANNELMODEIS

t_replyHandler	ModeCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	t_replyHandler	replyHandler;

	if (!target.getIsRegistered())
	{
		replyHandler.add(target.getFd(), ERR::NOTREGISTERED(target));
		return replyHandler;
	}

	if (_commandArray.size() < 3)
	{
		replyHandler.add(target.getFd(), ERR::NEEDMOREPARAMS(target, "MODE"));
		return replyHandler;
	}

	mapChannels::iterator index = ChannelArray.find(_commandArray[1]);
	if (index->first != _commandArray[1])
	{
		replyHandler.add(target.getFd(), ERR::NOSUCHCHANNEL(target, _commandArray[1]));
		return replyHandler;
	}

	Channel	channel = *index->second;
	char c = verifFlag();
	if (c)
	{
		replyHandler.add(target.getFd(), ERR::UNKNOWNMODE(target, channel, c));
		return replyHandler;
	}

	if (!isOper(target, channel))
	{
		replyHandler.add(target.getFd(), ERR::CHANOPRIVSNEEDED(target, channel));
		return replyHandler;
	}

	for (size_t i = 1; i < _commandArray.size(); i++)
	{
		for (size_t j = 1; _commandArray[i][j]; j++)
		{
			target.setMode(_commandArray[i][j], _commandArray[i][0]);
		}
	}

	replyHandler.add(target.getFd(), RPL::CHANNELMODEIS(target, channel));

	return replyHandler;
}

