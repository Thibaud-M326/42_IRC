#include "InviteCommand.hpp"

InviteCommand::InviteCommand(std::vector<std::string>& params): ACommand(params) {}

t_replyHandler	InviteCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	t_replyHandler	replyHandler;

	if (!target.getIsRegistered())
	{
		replyHandler.add(target.getFd(), ERR::NOTREGISTERED());
		return replyHandler;
	}

	if (_commandArray.size() != 3)
	{
		replyHandler.add(target.getFd(), ERR::NEEDMOREPARAMS("TOPIC"));
		return replyHandler;
	}

	Client	*tmp = findClientByNickName(_commandArray[1], buildClientVec(ClientArray));
	if (!tmp)
	{
		replyHandler.add(target.getFd(), ERR::NOSUCHNICK(_commandArray[1]));
		return replyHandler;
	}

	Channel	*channel = getChannelByName(_commandArray[2], ChannelArray);
	if (!channel)
	{
		replyHandler.add(target.getFd(), ERR::NOSUCHCHANNEL(_commandArray[1]));
		return replyHandler;
	}

	tmp = findClientByNickName(target.getNickname(), channel->getClientList());
	if (!tmp)
	{
		replyHandler.add(target.getFd(), ERR::NOTONCHANNEL(*channel));
		return replyHandler;
	}

	tmp = findClientByNickName(_commandArray[1], channel->getClientList());
	if (tmp)
	{
		replyHandler.add(target.getFd(), ERR::USERONCHANNEL(*channel, tmp->getUsername()));
		return replyHandler;
	}

	tmp = findClientByNickName(_commandArray[1], buildClientVec(ClientArray));
	if (channel->getMode()[inviteOnly])
	{
		if (isOper(target, *channel))
		{
			channel->addClient(tmp);
			tmp->joinChannel(channel->getName(), channel);
			replyHandler.add(channel->getClientsFd(), RPL::INVITING(*tmp, *channel));
		}
		else
			replyHandler.add(target.getFd(), ERR::CHANOPRIVSNEEDED(*channel));
	}
	else
	{
		channel->addClient(tmp);
		tmp->joinChannel(channel->getName(), channel);
		replyHandler.add(channel->getClientsFd(), RPL::INVITING(*tmp, *channel));
	}

	return replyHandler;
}

