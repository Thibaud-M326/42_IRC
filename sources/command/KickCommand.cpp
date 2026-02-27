#include "KickCommand.hpp"

KickCommand::KickCommand(std::vector<std::string>& params)
: 	ACommand(params),
	_comments("")
{}

//on a deux mode d execution de la commande
//un mode broadcast to all usr
//un mode one channel one user

//je fait une liste des channel
//une liste des utilisateur a kick

//si un seul channel -> on execute le kick sur tous les clients
//

//si plusieur channel -> on execute le kick sur un channel/client a la fois,

//une structure pour les deux cas, deja il va falloir parser la commande
//

//erreurs:
	//461 ERR_NEEDMOREPARAMS      // Pas assez de paramètres fournis (canal ou user manquant, ou mauvais nombre de serveur par rapport au user)
	//476 ERR_BADCHANMASK         // Nom de canal invalide (ex: ne commence pas par # ou &)
	//403 ERR_NOSUCHCHANNEL       // Le canal demandé n'existe pas sur le serveur
	//482 ERR_CHANOPRIVSNEEDED    // L'émetteur n'est pas opérateur (@) du canal
	//442 ERR_NOTONCHANNEL        // L'opérateur lui-même n'est pas dans le canal
	//441 ERR_USERNOTINCHANNEL    // La cible à kicker n'est pas dans le canal

//entree: KICK <channel> *( "," <channel> ) <user> *( "," <user> ) [:<comment>]
	//valide si :
		//un canal, plusieurs user
		//plusieur canaux, un user par canal sera kick

//invalide si :
    //plus de canaux que de users (ex: 3 canaux, 2 users)
    //plus de users que de canaux, sauf si canal unique

//sortie :
	//si une erreur est lance on l'envoi au sender uniquement
	//si la commande execute et kick quelqu'un on envoi a tous les membre du canal
	//si on a plusieurs execution, les exec qui marchent envoi a tous le monde,
	//celle qui marchent pas envoi erreur a l user qui send

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

bool	KickCommand::isUserOnChannel(std::string userName, Channel& channel)
{
	std::vector<Client*> clientList;

	clientList = channel.getClientList();
	for (std::vector<Client*>::iterator client = clientList.begin(); client != clientList.end(); client++)
	{
		if (userName == (*client)->getNickname())
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
		replyHandler.add(clientSource.getFd(), ERR::NOTONCHANNEL(clientSource, *chan));
		return;
	}

	std::vector<std::string>::iterator user;
	for (user = usersArg.begin(); user != usersArg.end(); user++)
	{
		std::cout << "channel arg:" << *user << std::endl;
		if (!isUserOnChannel(*user, *chan))
		{
			replyHandler.add(clientSource.getFd(), ERR::NOTONCHANNEL(clientSource, *chan));
			continue;
		}
		clientToKick = getUserOnChannel(*user, *chan);
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
