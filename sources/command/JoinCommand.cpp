#include "JoinCommand.hpp"

JoinCommand::JoinCommand(std::vector<std::string>& params): ACommand(params) {}

chanParams	JoinCommand::buildChannelParams(unsigned int& nbChan)
{
	chanParams	params;

	for (std::vector<std::string>::iterator word = _commandArray.begin(); word != _commandArray.end(); word++)
	{
		// parse chan name
		for (size_t index = 0; index < word->size(); index++)
		{
			size_t	nextWord = word->find(',', index);
			if (isValidChar((*word)[index]))
			{
				nbChan++;
				if (nextWord == std::string::npos)
				{
					params.push_back(std::make_pair(word->substr(index), ""));
					break ;
				}
				params.push_back(std::make_pair(word->substr(index, nextWord - index), ""));
				index = nextWord;
			}
		}
		// parse chan key
		for (size_t index = 0; index < word->size(); index++)
		{
			if (word == _commandArray.begin())
				break ;
			size_t	nextWord = word->find(',', index);
			if (isValidChar((*word)[index]))
				break ;
			if (nextWord == std::string::npos)
			{
				params.push_back(std::make_pair(word->substr(index), ""));
				break ;
			}
			params.push_back(std::make_pair(word->substr(index, nextWord - index), ""));
			index = nextWord;
		}
	}

	for (size_t i = 0; i < params.size(); i++)
	{
		if (i + nbChan < params.size())
		{
			params[i].second = params[i + nbChan].first;
			params.erase(params.begin() + (i + nbChan));
		}
	}

	return params;
}

void	JoinCommand::createChannel(mapChannels& ChannelArray, chanParams params, Client& ope)
{
	for (chanParams::iterator it = params.begin(); it != params.end(); it++)
	{
		if (ChannelArray.find(it->first) == ChannelArray.end())
		{
			Channel	*chan = new Channel();
			chan->setName(it->first);
			chan->setKey(it->second);
			chan->addOperator(&ope);
			ChannelArray.insert(std::make_pair(it->first, chan));
		}
	}
}

void	JoinCommand::joinChannel(mapChannels& ChannelArray, chanParams params,
					Client& target, t_replyHandler& replyHandler)
{
	size_t	index = 0;

	for (chanParams::iterator it = params.begin(); it != params.end(); it++)
	{
		mapChannels::iterator chanToJoin = ChannelArray.find(it->first);

		if (chanToJoin != ChannelArray.end())
		{
			if (chanToJoin->second->getMode()[inviteOnly] && !chanToJoin->second->isWhiteListed(target))
			{
				replyHandler.add(target.getFd(), ERR::INVITEONLYCHAN(target, *chanToJoin->second));
			}
			else if (static_cast<ssize_t>(chanToJoin->second->getClientList().size()) == chanToJoin->second->getLimitNbUser())
			{
				replyHandler.add(target.getFd(), ERR::CHANNELISFULL(target, *chanToJoin->second));
			}
			else if (chanToJoin->second->getKey() != params[index].second)
			{
				replyHandler.add(target.getFd(), ERR::BADCHANNELKEY(target, *chanToJoin->second));
			}
			else if (it->second == chanToJoin->second->getKey())
			{
				target.joinChannel(chanToJoin->first, chanToJoin->second);
				chanToJoin->second->addClient(&target);
				chanToJoin->second->delFromWhiteList(target);
				replyHandler.add(chanToJoin->second->getClientsFd(), RPL::JOIN(target, chanToJoin->first, chanToJoin->second->getKey()));

				if (chanToJoin->second->getTopic().empty())
					replyHandler.add(target.getFd(), RPL::NOTOPIC(target, *chanToJoin->second));
				else
					replyHandler.add(target.getFd(), RPL::TOPIC(target, *chanToJoin->second));

				replyHandler.add(target.getFd(), RPL::NAMREPLY(target, *chanToJoin->second));
				replyHandler.add(target.getFd(), RPL::ENDOFNAMES(target, *chanToJoin->second));
			}
			else
				replyHandler.add(target.getFd(), ERR::BADCHANNELKEY(target, *chanToJoin->second));
		}
		index++;
	}
}

t_replyHandler	JoinCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	t_replyHandler	replyHandler;
	unsigned int	nbChan = 0;

	if (!target.getIsRegistered())
	{
		replyHandler.add(target.getFd(), ERR::NOTREGISTERED(target));
		return replyHandler;
	}

	chanParams	params = buildChannelParams(nbChan);

	mapChannels	tmpChannelList(target.getChannelList());
	if (_commandArray[1] == "0")
	{
		for (mapChannels::iterator it = tmpChannelList.begin(); it != tmpChannelList.end(); it++)
		{
			replyHandler.add(it->second->getClientsFd(), RPL::PART(target, *it->second, "Leaving"));
			it->second->removeClient(&target);
		}
		target.clearChannel();
		return replyHandler;
	}

	if (params.empty())
	{
		replyHandler.add(target.getFd(), ERR::NEEDMOREPARAMS(target, "JOIN"));
		return replyHandler;
	}
	else if (!params.empty() && nbChan == 0)
	{
		for (chanParams::iterator it = params.begin(); it != params.end(); it++)
			replyHandler.add(target.getFd(), ERR::NOSUCHCHANNEL(target, it->second));
		return replyHandler;
	}

	createChannel(ChannelArray, params, target);
	joinChannel(ChannelArray, params, target, replyHandler);

	return replyHandler;
}

