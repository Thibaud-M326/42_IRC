#include "PrivMsgCommand.hpp"
#include <vector>
#include <algorithm>


#include <iostream>

PrivMsgCommand::PrivMsgCommand(std::vector<std::string>& params): ACommand(params) {}


//       Command: PRIVMSG
//    Parameters: <msgtarget> <text to be sent>

//optionel :

// ERR_CANNOTSENDTOCHAN

// ERR_NORECIPIENT :OK

// ERR_NOTEXTTOSEND :OK

// ERR_TOOMANYTARGETS :TODO

// ERR_NOSUCHNICK : OK

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

t_replyHandler	PrivMsgCommand::sendPrivMsgToNickname(Client& clientSource, mapClients& clientArray, t_replyHandler& replyHandler)
{
	std::string	clientDestNickname = _commandArray[1];
	std::string	message = _commandArray[2];
	Client* clientDest = NULL;

	if (message[0] == ':')
		message.erase(0, 1);

	clientDest = findClientByNickName(clientDestNickname, clientArray);
	if (!clientDest)
	{
		replyHandler.add(clientSource.getFd(), ERR::NOSUCHNICK(clientSource, _commandArray[1]));
		return replyHandler;
	}
	
	if(clientDest->getFd() == clientSource.getFd())
	{
		replyHandler.add(clientSource.getFd(), RPL::PRIVMSG(clientSource, clientDest->getNickname(), message));
		return replyHandler;
	}
	else
	{
		replyHandler.add(clientDest->getFd(), RPL::PRIVMSG(clientSource, clientDest->getNickname(), message));
	}
	return replyHandler;
}

t_replyHandler	PrivMsgCommand::sendPrivMsgToChannel(Channel& chan, Client& clientSource, t_replyHandler& replyHandler)
{
	std::string	message = _commandArray[2];

	if (message[0] == ':')
		message.erase(0, 1);

	std::vector<Client*> clients;
	clients = chan.getClientList();

	for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); it++)	
	{
		Client* clientDest = *it;
		if (clientDest->getFd() != clientSource.getFd())
			replyHandler.add(clientDest->getFd(), RPL::PRIVMSG(clientSource, chan.getName(), message));
	}

	return replyHandler;
}

t_replyHandler	PrivMsgCommand::ExecuteCommand(Client& clientSource, mapClients& clientArray, mapChannels& ChannelArray) 
{
	t_replyHandler	replyHandler;
	Channel*		chan;

	if (!clientSource.getIsRegistered())
	{
		replyHandler.add(clientSource.getFd(), ERR::NOTREGISTERED(clientSource));
		return replyHandler;
	}

	if (!isValidPrivMsg(clientSource, clientArray, replyHandler))
		return replyHandler;

		
	if ((chan = getChannelByName(_commandArray[1], ChannelArray)))
		sendPrivMsgToChannel(*chan, clientSource, replyHandler);
	else
		sendPrivMsgToNickname(clientSource, clientArray, replyHandler);

	return replyHandler;
}
