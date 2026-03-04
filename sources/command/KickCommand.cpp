#include "KickCommand.hpp"

KickCommand::KickCommand(std::vector<std::string>& params)
: 	ACommand(params),
	_comments("")
{}

std::vector<std::string>	KickCommand::splitByComma(std::string argsToSplit)
{
	std::vector<std::string> argsSplitted;
	std::string t;
	char del = ',';

	std::stringstream ss(argsToSplit);

	while (std::getline(ss, t, del))
	{
		argsSplitted.push_back(t);
	}

	return argsSplitted;	
}

bool	KickCommand::isOperator(Client& clientSource, Channel& channel)
{
	std::vector<Client*> channelOp = channel.getOperators();

	for (std::vector<Client*>::iterator	it = channelOp.begin(); it != channelOp.end(); it++)
	{
		if (*it == &clientSource)
			return true;
	}
	return false;
}

bool	KickCommand::isOperatorOnCanal(Client& clientSource, Channel& channel)
{
	std::vector<int> clientsFds;

	clientsFds = channel.getClientsFd();

	for (std::vector<int>::iterator fd = clientsFds.begin(); fd != clientsFds.end(); fd++)
	{
		if (clientSource.getFd() == *fd)
			return true;
	}
	return false;
}

Client* KickCommand::getUserOnChannel(std::string userName, Channel& channel)
{
	Client* clientOnChan;
	std::vector<Client*> clientList;

	clientList = channel.getClientList();
	for (std::vector<Client*>::iterator client = clientList.begin(); client != clientList.end(); client++)
	{
		if (userName == (*client)->getNickname())
		{
			return clientOnChan = (*client);	
		}
	}
	return clientOnChan = NULL;	
}

//parcourir la liste des channel du client et celle du channel
//enlever le client au deux listes
//ajouter au replyHandler
void	KickCommand::kickUsersFromChannel(Client& clientSource, mapChannels& channelArray, t_replyHandler& replyHandler)
{
	Client*	clientToKick;
	Channel* chan;
	std::vector<std::string> usersArg;

	usersArg = splitByComma(_commandArray[2]);
	chan = getChannelByName(_commandArray[1], channelArray);

	if (!isOperator(clientSource, *chan))
	{
		replyHandler.add(clientSource.getFd(), ERR::CHANOPRIVSNEEDED(clientSource, *chan));
		return;
	}

	if (!isOperatorOnCanal(clientSource, *chan))
	{
		replyHandler.add(clientSource.getFd(), ERR::NOTONCHANNEL(clientSource.getNickname(), *chan));
		return;
	}

	std::vector<std::string>::iterator user;
	for (user = usersArg.begin(); user != usersArg.end(); user++)
	{
		std::cout << "channel arg:" << *user << std::endl;

		clientToKick = getUserOnChannel(*user, *chan);
		if (!clientToKick)
		{
			replyHandler.add(clientSource.getFd(), ERR::NOTONCHANNEL(_commandArray[2], *chan));
			continue;
		}
		clientToKick->leaveChannel(chan);
		replyHandler.add(chan->getClientsFd(), RPL::KICK(clientSource, chan->getName(), clientToKick->getNickname(), _comments));
		chan->removeOperator(clientToKick);
		chan->removeClient(clientToKick);
	}
}

t_replyHandler	KickCommand::ExecuteCommand(Client& clientSource, mapClients& clientArray, mapChannels& channelArray)
{
	(void)clientArray;
	t_replyHandler	replyHandler;

	//clientIsConnected
	if (!clientSource.getIsRegistered())
	{
		replyHandler.add(clientSource.getFd(), ERR::NOTREGISTERED(clientSource));
		return replyHandler;
	}

	//argumentNumberAreValid
	if (_commandArray.size() < 3 || _commandArray[1].size() == 0 || _commandArray[2].size() == 0)
	{
		replyHandler.add(clientSource.getFd(), ERR::NEEDMOREPARAMS(clientSource, "KICK"));
		return replyHandler;
	}
	
	//getReason
	if (_commandArray.size() == 4)
		_comments = _commandArray[3];

	//chanParamValid
	if (!isValidChar(_commandArray[1][0]))
	{
		replyHandler.add(clientSource.getFd(), ERR::BADCHANMASK(clientSource, _commandArray[1]));
		return replyHandler;
	}

	Channel	*chanSource = getChannelByName(_commandArray[1], channelArray);
	if (!chanSource)
	{
		replyHandler.add(clientSource.getFd(), ERR::NOSUCHCHANNEL(clientSource, _commandArray[1]));
		return replyHandler;
	}

	kickUsersFromChannel(clientSource, channelArray, replyHandler);

	return replyHandler;
}

