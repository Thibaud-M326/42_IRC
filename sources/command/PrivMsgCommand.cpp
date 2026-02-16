#include "PrivMsgCommand.hpp"

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



bool	PrivMsgCommand::isValidPrivMsg(Client& target, mapClients& ClientArray, t_replyHandler& replyHandler)
{
	(void)ClientArray;

	if (_commandArray.size() == 1 || _commandArray[1].size() == 0)
	{
		replyHandler.add(target.getFd(), ERR::NORECIPIENT(target, _commandArray[0]));
		return false;
	}

	if (_commandArray.size() == 3 || _commandArray[2].size() == 0)
	{
		replyHandler.add(target.getFd(), ERR::NOTEXTTOSEND(target));
		return false;
	}

	// if (_commandArray.size() > 3)
	// {
	// 	replyHandler.add(target.getFd(), ERR::TOOMANYTARGETS(target));
	// 	return false;
	// }
	
	return true;
}

t_replyHandler	PrivMsgCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray) {
	(void)ClientArray;
	(void)ChannelArray;
	(void)target;
	t_replyHandler	replyHandler;

	if (!target.getIsRegistered())
	{
		replyHandler.add(target.getFd(), ERR::NOTREGISTERED(target));
		return replyHandler;
	}

	for (std::vector<std::string>::iterator it = _commandArray.begin(); it != _commandArray.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	if (!isValidPrivMsg(target, ClientArray, replyHandler))
		return replyHandler;

	// if (isChannel(_commandArray[1], ChannelArray))
		// vaeo	
	else
		//send to USER



	return replyHandler;
}
