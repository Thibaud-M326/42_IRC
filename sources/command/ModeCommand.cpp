#include "ModeCommand.hpp"
#include "Irc.hpp"

ModeCommand::ModeCommand(std::vector<std::string>& params): ACommand(params) {}

char	ModeCommand::isValidFlag(char mode)
{
	for (size_t i = 0; ircMacro::modeCharArray[i]; i++)
	{
		if (mode == ircMacro::modeCharArray[i]
				|| mode == '-'
				|| mode == '+')
			return mode;
	}
	return '\0';
}

char	ModeCommand::verifFlag()
{
	for (size_t j = 0; _commandArray[2][j]; j++)
	{
		char mode = isValidFlag(_commandArray[2][j]);
		if (mode)
			return mode;
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

void	ModeCommand::modeUserLimit(char& signMode, size_t& count, t_replyHandler& replyHandler)
{
	if (signMode == '+')
	{
		if (count + 3 < _commandArray.size())
		{
			std::istringstream iss(_commandArray[count + 3]);
			long	limit;
			char	end;

			iss >> limit >> end;
			if (limit >= 0 && end == '\0')
			{
				_channel->setLimitNbUser(limit);
				_channel->setMode(userLimit, true);
			}
		}
		else
		{
			replyHandler.add(_client.getFd(), ERR::NEEDMOREPARAMS(_client, "MODE (l)"));
		}
	}
	else
	{
		_channel->setLimitNbUser(-1);
		_channel->setMode(userLimit, false);
	}
	count++;
}

void	ModeCommand::modeInvitOnly(char& signMode, size_t& count)
{
	if (signMode == '+')
	{
		_channel->setMode(inviteOnly, true);
	}
	else
	{
		_channel->setMode(inviteOnly, false);
	}
	count++;
}

void	ModeCommand::modeTopicRestriction(char& signMode, size_t& count)
{
	if (signMode == '+')
	{
		_channel->setMode(restrictTopic, true);
	}
	else
	{
		_channel->setMode(restrictTopic, false);
	}
	count++;
}

void	ModeCommand::modeOperatorPrivilege(char& signMode, size_t& count, t_replyHandler& replyHandler)
{

	if (count + 3 < _commandArray.size())
	{
		Client	*target = findClientByNickName(_commandArray[count + 3], _channel->getClientList());
		if (!target)
		{
			replyHandler.add(_client.getFd(), ERR::USERNOTINCHANNEL(_client, *_channel, _commandArray[count + 3]));
		}
		else if (signMode == '+')
		{
			_channel->addOperator(target);
			replyHandler.add(target->getFd(), RPL::YOUREOPER(*target));
		}
		else
		{
			_channel->removeOperator(target);
		}
	}
	else
	{
		replyHandler.add(_client.getFd(), ERR::NEEDMOREPARAMS(_client, "MODE (o)"));
	}
	count++;
}

void	ModeCommand::modeChannelKey(char& signMode, size_t& count, t_replyHandler& replyHandler)
{
	if (signMode == '+')
	{
		if (count + 3 < _commandArray.size())
		{
			if (!_channel->getKey().empty())
			{
				_channel->setKey(_commandArray[count + 3]);
				_channel->setMode(operatorPrivileges, true);
			}
			else
			{
				replyHandler.add(_client.getFd(), ERR::KEYSET(_client, *_channel));
			}
		}
		else
		{
			replyHandler.add(_client.getFd(), ERR::NEEDMOREPARAMS(_client, "MODE (k)"));
		}
	}
	else
	{
		_channel->setKey("");
		_channel->setMode(operatorPrivileges, false);
	}
	count++;
}

void	ModeCommand::handleMode(t_replyHandler& replyHandler)
{
	std::string modeString = _commandArray[2];
	char		signMode = '\0';
	size_t		count = 1;

	for (size_t i = 0; i < modeString.size(); i++)
	{
		if (modeString[i] == '-' || modeString[i] == '+')
		{
			signMode = modeString[i];
			i++;
		}
		switch (modeString[i])
		{
			case ircMacro::modeCharArray[userLimit]:
			{
				modeUserLimit(signMode, count, replyHandler);
				break ;
			}
			case ircMacro::modeCharArray[operatorPrivileges]:
			{
				modeOperatorPrivilege(signMode, count, replyHandler);
				break ;
			}
			case ircMacro::modeCharArray[restrictPassword]:
			{
				modeChannelKey(signMode, count, replyHandler);
				break ;
			}
			case ircMacro::modeCharArray[restrictTopic]:
			{
				modeTopicRestriction(signMode, count);
				break ;
			}
			case ircMacro::modeCharArray[inviteOnly]:
			{
				modeInvitOnly(signMode, count);
				break ;
			}
			case ircMacro::modeCharArray[failure]:
			{
				return ;
			}
		}
	}
}

t_replyHandler	ModeCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	t_replyHandler	replyHandler;

	if (!target.getIsRegistered())
	{
		replyHandler.add(target.getFd(), ERR::NOTREGISTERED(target));
		return replyHandler;
	}

	if (_commandArray.size() == 1)
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

	_channel = index->second;

	Client	*tmp = findClientByNickName(target.getNickname(), _channel->getClientList());

	if (!tmp)
	{
		replyHandler.add(target.getFd(), ERR::USERNOTINCHANNEL(target, *_channel, target.getNickname()));
		return replyHandler;
	}

	_client = target;
	
	if (!isOper(target, *_channel))
	{
		replyHandler.add(target.getFd(), ERR::CHANOPRIVSNEEDED(target, *_channel));
		return replyHandler;
	}

	char c = verifFlag();
	if (!c)
	{
		replyHandler.add(target.getFd(), ERR::UNKNOWNMODE(target, *_channel, c));
		std::cout << "NO MODE" <<std::endl;
		return replyHandler;
	}

	replyHandler.add(_channel->getClientsFd(), RPL::CHANNELMODEIS(target, *_channel));

	return replyHandler;
}

