#include "PrivMsgCommand.hpp"
#include <vector>

#include <iostream>

PrivMsgCommand::PrivMsgCommand(std::vector<std::string>& params): ACommand(params) {}


//       Command: PRIVMSG
//    Parameters: <msgtarget> <text to be sent>

//optionel :
    //    404    ERR_CANNOTSENDTOCHAN
    //           "<channel name> :Cannot send to channel"


// ERR_NORECIPIENT
// :Pas de destinataire donné (<commande>)

// ERR_NOTEXTTOSEND
// :Pas de texte à envoyer

//407    ERR_TOOMANYTARGETS
//Returned to a client which trying to send a
//PRIVMSG/NOTICE to too many recipients.

//401    ERR_NOSUCHNICK
//       "<nickname> :No such nick/channel"
//       -Used to indicate the nickname parameter supplied to a
//       command is currently unused.

//301    RPL_AWAY
//       "<nick> :<away message>"

bool	PrivMsgCommand::isValidPrivMsg(Client& clientSource, mapClients& clientArray, t_replyHandler& replyHandler)
{
	(void)clientArray;

	if (_commandArray.size() == 1 || _commandArray[1].size() == 0)
	{
		replyHandler.add(clientSource.getFd(), ERR::NORECIPIENT(clientSource, _commandArray[0]));
		return false;
	}

	if (_commandArray.size() == 2 || _commandArray[2].size() == 0)
	{
		replyHandler.add(clientSource.getFd(), ERR::NOTEXTTOSEND(clientSource));
		return false;
	}

	//trop de clientSource separe par des virgules
	if (_commandArray.size() > 3)
	{
		replyHandler.add(clientSource.getFd(), ERR::TOOMANYTARGETS(clientSource, _commandArray[1]));
		return false;
	}
	
	return true;
}

//je dois trouver le bon client a qui envoyer le message
//je dois ajouter le message au reply handler
t_replyHandler	PrivMsgCommand::sendPrivMsgToNickname(Client& clientSource, mapClients& clientArray, t_replyHandler& replyHandler)
{
	std::string	clientDestNickname = _commandArray[1];
	std::string	awayMessage = _commandArray[2];
	Client* clientDest = NULL;

	clientDest = findClientByNickName(clientDestNickname, clientArray);
	if (!clientDest)
	{
		replyHandler.add(clientSource.getFd(), ERR::NOSUCHNICK(clientSource, _commandArray[1]));
		return replyHandler;
	}

	std::vector<int> sendList;
	sendList.push_back(clientSource.getFd());
	sendList.push_back(clientDest->getFd());

	replyHandler.add(sendList, RPL::AWAY(clientSource, awayMessage));

	return replyHandler;
}

t_replyHandler	PrivMsgCommand::ExecuteCommand(Client& clientSource, mapClients& clientArray, mapChannels& ChannelArray) {
	(void)clientArray;
	(void)ChannelArray;
	(void)clientSource;
	t_replyHandler	replyHandler;

	if (!clientSource.getIsRegistered())
	{
		replyHandler.add(clientSource.getFd(), ERR::NOTREGISTERED(clientSource));
		return replyHandler;
	}

	for (std::vector<std::string>::iterator it = _commandArray.begin(); it != _commandArray.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	if (!isValidPrivMsg(clientSource, clientArray, replyHandler))
		return replyHandler;

	// if (isChannel(_commandArray[1], ChannelArray))
		// vaeo	
	// else
		//send to USER	

	sendPrivMsgToNickname(clientSource, clientArray, replyHandler);

	return replyHandler;
}
