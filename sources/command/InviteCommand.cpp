#include "InviteCommand.hpp"

InviteCommand::InviteCommand(std::vector<std::string>& params): ACommand(params) {}

void	InviteCommand::addToChannel(Client& target, Channel& channel, t_replyHandler& replyHandler)
{
	channel.addWhiteList(target);
	replyHandler.add(channel.getClientsFd(), RPL::INVITING(target, channel, _commandArray[1]));
}

t_replyHandler	InviteCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	t_replyHandler	replyHandler;

	if (!target.getIsRegistered())
	{
		replyHandler.add(target.getFd(), ERR::NOTREGISTERED(target));
		return replyHandler;
	}

	if (_commandArray.size() != 3)
	{
		replyHandler.add(target.getFd(), ERR::NEEDMOREPARAMS(target, "INVITE"));
		return replyHandler;
	}

	Client	*tmp = findClientByNickName(_commandArray[1], buildClientVec(ClientArray));
	if (!tmp)
	{
		replyHandler.add(target.getFd(), ERR::NOSUCHNICK(target, _commandArray[1]));
		return replyHandler;
	}

	Channel	*channel = getChannelByName(_commandArray[2], ChannelArray);
	if (!channel)
	{
		replyHandler.add(target.getFd(), ERR::NOSUCHCHANNEL(target, _commandArray[1]));
		return replyHandler;
	}

	tmp = findClientByNickName(target.getNickname(), channel->getClientList());
	if (!tmp)
	{
		replyHandler.add(target.getFd(), ERR::NOTONCHANNEL(target, *channel));
		return replyHandler;
	}

	tmp = findClientByNickName(_commandArray[1], channel->getClientList());
	if (tmp)
	{
		replyHandler.add(target.getFd(), ERR::USERONCHANNEL(target, *channel, tmp->getUsername()));
		return replyHandler;
	}

	tmp = findClientByNickName(_commandArray[1], buildClientVec(ClientArray));
	if (channel->getMode()[inviteOnly])
	{
		if (isOper(target, *channel))
			addToChannel(*tmp, *channel, replyHandler);
		else
			replyHandler.add(target.getFd(), ERR::CHANOPRIVSNEEDED(target, *channel));
	}
	else
		addToChannel(*tmp, *channel, replyHandler);

	return replyHandler;
}

