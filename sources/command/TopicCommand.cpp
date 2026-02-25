#include "TopicCommand.hpp"

TopicCommand::TopicCommand(std::vector<std::string>& params): ACommand(params) {}

t_replyHandler	TopicCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	t_replyHandler	replyHandler;

	if (!target.getIsRegistered())
	{
		replyHandler.add(target.getFd(), ERR::NOTREGISTERED());
		return replyHandler;
	}

	if (_commandArray.size() == 1)
	{
		replyHandler.add(target.getFd(), ERR::NEEDMOREPARAMS("TOPIC"));
		return replyHandler;
	}

	Channel	*channel = getChannelByName(_commandArray[1], ChannelArray);
	if (!channel)
	{
		replyHandler.add(target.getFd(), ERR::NOSUCHCHANNEL(_commandArray[1]));
		return replyHandler;
	}

	Client	*tmp = findClientByNickName(target.getNickname(), channel->getClientList());

	if (!tmp)
	{
		replyHandler.add(target.getFd(), ERR::NOTONCHANNEL(*channel));
		return replyHandler;
	}

	if (_commandArray.size() == 2)
	{
		if (channel->getTopic().empty())
			replyHandler.add(target.getFd(), RPL::NOTOPIC(*channel));
		else
			replyHandler.add(target.getFd(), RPL::NOTOPIC(*channel));
	}
	else
	{
		if (channel->getMode()[restrictTopic])
		{
			if (isOper(target, *channel))
			{
				channel->setTopic(&_commandArray[2][1]);
				if (channel->getTopic().empty())
					replyHandler.add(channel->getClientsFd(), RPL::NOTOPIC(*channel));
				else
					replyHandler.add(channel->getClientsFd(), RPL::TOPIC(*channel));
			}
			else
				replyHandler.add(target.getFd(), ERR::CHANOPRIVSNEEDED(*channel));
		}
		else
		{
			channel->setTopic(&_commandArray[2][1]);
			if (channel->getTopic().empty())
				replyHandler.add(channel->getClientsFd(), RPL::NOTOPIC(*channel));
			else
				replyHandler.add(channel->getClientsFd(), RPL::TOPIC(*channel));
		}
	}

	return replyHandler;
}
