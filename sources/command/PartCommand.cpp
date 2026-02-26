#include "PartCommand.hpp"

PartCommand::PartCommand(std::vector<std::string>& params): ACommand(params) {}

// Parameters: <channel> *( "," <channel> ) [ <Part Message> ]
//
// The PART command causes the user sending the message to be removed
// from the list of active members for all given channels listed in the
// parameter string.  If a "Part Message" is given, this will be sent
// instead of the default message, the nickname.  This request is always
// granted by the server.
//
// Servers MUST be able to parse arguments in the form of a list of
// target, but SHOULD NOT use lists when sending PART messages to
// clients.
//
// Numeric Replies:
//
//         ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
//         ERR_NOTONCHANNEL

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
			replyHandler.add(target.getFd(), ERR::NOTONCHANNEL(target, *chanToPart));
			continue ;
		}
		replyHandler.add(chanToPart->getClientsFd(), RPL::PART(target, *chanToPart, reason));
		chanToPart->removeClient(tmp);
		tmp->leaveChannel(chanToPart);

		mapChannels	map = target.getChannelList();
		for (mapChannels::iterator i = map.begin(); i != map.end(); i++)
		{
			std::cout << "===========\nPART\nCHANNEL CLIENT == |" << i->first << "|\n===========\n";
		}
	}

	return replyHandler;
}

