#include "ModeCommand.hpp"

ModeCommand::ModeCommand(std::vector<std::string>& params): ACommand(params) {}

char	ModeCommand::isValidFlag(char mode)
{
	for (size_t i = 0; ircMacro::modeCharArray[i]; i++)
	{
		if (mode == ircMacro::modeCharArray[i]
				|| mode == '-'
				|| mode == '+'
				|| mode == '\0')
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

void	ModeCommand::modeUserLimit(Client& target, char& signMode, size_t& count, t_replyHandler& replyHandler)
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
			replyHandler.add(_client.getFd(), ERR::NEEDMOREPARAMS(target, "MODE (l)"));
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

void	ModeCommand::modeOperatorPrivilege(Client& clientSource, char& signMode, size_t& count, t_replyHandler& replyHandler)
{
	if (count + 3 < _commandArray.size())
	{
		Client	*target = findClientByNickName(_commandArray[count + 3], _channel->getClientList());
		if (!target)
		{
			replyHandler.add(_client.getFd(), ERR::USERNOTINCHANNEL(clientSource, *_channel, _commandArray[count + 3]));
		}
		else if (signMode == '+')
		{
			_channel->addOperator(target);
			replyHandler.add(_channel->getClientsFd(), RPL::MODE(clientSource, *_channel, target->getNickname()));
		}
		else
		{
			_channel->removeOperator(target);
		}
	}
	else
	{
		replyHandler.add(_client.getFd(), ERR::NEEDMOREPARAMS(clientSource, "MODE (o)"));
	}
	count++;
}

void	ModeCommand::modeChannelKey(Client& target, char& signMode, size_t& count, t_replyHandler& replyHandler)
{
	if (signMode == '+')
	{
		if (count + 3 < _commandArray.size())
		{
			if (!_channel->getKey().empty())
			{
				_channel->setKey(_commandArray[count + 3]);
				_channel->setMode(restrictPassword, true);
			}
			else
			{
				replyHandler.add(_client.getFd(), ERR::KEYSET(target, *_channel));
			}
		}
		else
		{
			replyHandler.add(_client.getFd(), ERR::NEEDMOREPARAMS(target, "MODE (k)"));
		}
	}
	else
	{
		_channel->setKey("");
		_channel->setMode(restrictPassword, false);
	}
	count++;
}

void	ModeCommand::handleMode(Client& target, t_replyHandler& replyHandler)
{
	std::string modeString = _commandArray[2];
	char		signMode = '\0';
	size_t		count = 0;

	for (size_t i = 0; i < modeString.size(); i++)
	{
		if (modeString[i] == '-' || modeString[i] == '+')
		{
			signMode = modeString[i];
			i++;
		}
		switch (modeString[i])
		{
			case ircMacro::modeUserLimit:
			{
				modeUserLimit(target, signMode, count, replyHandler);
				break ;
			}
			case ircMacro::modeOperatorPrivileges:
			{
				modeOperatorPrivilege(target, signMode, count, replyHandler);
				break ;
			}
			case ircMacro::modeRestrictPassword:
			{
				modeChannelKey(target, signMode, count, replyHandler);
				break ;
			}
			case ircMacro::modeRestrictTopic:
			{
				modeTopicRestriction(signMode, count);
				break ;
			}
			case ircMacro::modeInviteOnly:
			{
				modeInvitOnly(signMode, count);
				break ;
			}
			case ircMacro::modeFailure:
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

	_channel = getChannelByName(_commandArray[1], ChannelArray);
	if (!_channel)
	{
		replyHandler.add(target.getFd(), ERR::NOSUCHCHANNEL(target, _commandArray[1]));
		return replyHandler;
	}

	Client	*tmp = findClientByNickName(target.getNickname(), _channel->getClientList());

	if (!tmp)
	{
		replyHandler.add(target.getFd(), ERR::NOTONCHANNEL(target, *_channel));
		return replyHandler;
	}

	if (_commandArray.size() == 2)
	{
		replyHandler.add(target.getFd(), RPL::CHANNELMODEIS(target, *_channel));
		return replyHandler;
	}

	_client = target;
	
	if (!isOper(target, *_channel))
	{
		replyHandler.add(target.getFd(), ERR::CHANOPRIVSNEEDED(target, *_channel));
		return replyHandler;
	}

	if (_commandArray.size() > 2)
	{
		char c = verifFlag();
		if (!c)
		{
			replyHandler.add(target.getFd(), ERR::UNKNOWNMODE(target, *_channel, c));
			return replyHandler;
		}
	}

	handleMode(target, replyHandler);

	for (size_t i = 0; i < _channel->getClientList().size(); i++)
		replyHandler.add(_channel->getClientList()[i]->getFd(), RPL::CHANNELMODEIS(*_channel->getClientList()[i], *_channel));

	return replyHandler;
}

