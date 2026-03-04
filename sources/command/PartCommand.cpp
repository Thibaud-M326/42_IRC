#include "PartCommand.hpp"

PartCommand::PartCommand(std::vector<std::string>& params): ACommand(params) {}

void	PartCommand::eraseChannel(Channel* chan, mapChannels& ChannelArray)
{
	for (mapChannels::iterator it = ChannelArray.begin(); it != ChannelArray.end(); )
	{

		if (it->second == chan)
		{
			mapChannels::iterator	tmp = it++;
			ChannelArray.erase(tmp);
			delete chan;
		}
		else
			it++;
	}
}

t_replyHandler	PartCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	t_replyHandler	replyHandler;

	if (!target.getIsRegistered())
	{
		replyHandler.add(target.getFd(), ERR::NOTREGISTERED(target));
		return replyHandler;
	}

	if (_commandArray.size() < 3)
	{
		replyHandler.add(target.getFd(), ERR::NEEDMOREPARAMS(target, "PART"));
		return replyHandler;
	}

	std::string	reason = "";

	if (_commandArray.size() == 3)
	{
		if (_commandArray[2][0] == ':')
			reason = _commandArray[2].substr(1);
		else
			reason = _commandArray[2].substr();
	}

	for (size_t i = 0; i < _commandArray[1].size(); i++)
	{
		size_t		endChan = _commandArray[1].find(",");
		std::string	str;

		if (endChan == std::string::npos)
		{
			str = _commandArray[1].substr(i);
			i = _commandArray[1].size();
		}
		else
		{
			str = _commandArray[1].substr(i, endChan - 1);
			i = endChan;
		}
		Channel	*chanToPart = getChannelByName(str, ChannelArray);
		if (!chanToPart)
		{
			replyHandler.add(target.getFd(), ERR::NOSUCHCHANNEL(target, str));
			continue ;
		}
		Client	*tmp = findClientByNickName(target.getNickname(), chanToPart->getClientList());
		if (!tmp)
		{
			replyHandler.add(target.getFd(), ERR::NOTONCHANNEL(target.getNickname(), *chanToPart));
			continue ;
		}
		replyHandler.add(chanToPart->getClientsFd(), RPL::PART(target, *chanToPart, reason));
		chanToPart->removeOperator(tmp);
		chanToPart->removeClient(tmp);
		tmp->leaveChannel(chanToPart);
		if (chanToPart->getClientList().size() == 0)
		{
			eraseChannel(chanToPart, ChannelArray);
		}
	}
	return replyHandler;
}

