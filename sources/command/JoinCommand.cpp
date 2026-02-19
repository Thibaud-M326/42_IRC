#include "Channel.hpp"
#include "Client.hpp"
#include "JoinCommand.hpp"
#include "Reply.hpp"
#include "Irc.hpp"

// - JOIN - Used by a user to request to start listening to the specific channel.
// Note that this message accepts a special argument ("0"), which is a
// special request to leave all channels the user is currently a member of.
// 
// ```ruby
// Parameters: ( \<channel> *( "," \<channel> ) [ \<key> *( "," \<key> ) ] )
//                / "0"
// ```
// 
// - Numeric Replies:
// 
//            ERR_NEEDMOREPARAMS              
//            ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
//            ERR_CHANNELISFULL               ERR_BADCHANMASK
//            ERR_NOSUCHCHANNEL               
//			  RPL_TOPIC

JoinCommand::JoinCommand(std::vector<std::string>& params): ACommand(params) {}

bool	JoinCommand::isValidChar(char c)
{
	for (int i = 0; ircMacro::chanCharArray[i]; i++)
		if (c == ircMacro::chanCharArray[i])
			return true;
	return false;
}

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

void	JoinCommand::createChannel(mapChannels& ChannelArray, chanParams params)
{
	for (chanParams::iterator it = params.begin(); it != params.end(); it++)
	{
		if (ChannelArray.find(it->first) == ChannelArray.end())
		{
			Channel	*chan = new Channel();
			chan->setName(it->first);
			chan->setKey(it->second);
			ChannelArray.insert(std::make_pair(it->first, chan));
		}
	}
}

void	JoinCommand::joinChannel(mapChannels& ChannelArray, chanParams params,
					Client& target, t_replyHandler& replyHandler)
{
	for (chanParams::iterator it = params.begin(); it != params.end(); it++)
	{
		mapChannels::iterator chanToJoin = ChannelArray.find(it->first);

		if (chanToJoin != ChannelArray.end())
		{
			if (chanToJoin->second->getMode()[inviteOnly])
			{
				replyHandler.add(target.getFd(), ERR::INVITEONLYCHAN(target, *chanToJoin->second));
				return ;
			}
			if (it->second == chanToJoin->second->getKey())
			{
				target.joinChannel(chanToJoin->first, chanToJoin->second);
				chanToJoin->second->addClient(&target);
				replyHandler.add(chanToJoin->second->getClientsFd(), RPL::JOIN(target, it->first, it->second));
			}
			else
				replyHandler.add(target.getFd(), ERR::BADCHANNELKEY(target, *chanToJoin->second));
		}
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
	if (params.begin()->second == "0")
	{
		for (mapChannels::iterator it = tmpChannelList.begin(); it != tmpChannelList.end(); it++)
		{
			it->second->removeClient(&target);
			replyHandler.add(it->second->getClientsFd(), RPL::JOINQUIT(target, it->first));
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

	createChannel(ChannelArray, params);
	joinChannel(ChannelArray, params, target, replyHandler);

	return replyHandler;
}
