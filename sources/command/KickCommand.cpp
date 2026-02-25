#include "KickCommand.hpp"

KickCommand::KickCommand(std::vector<std::string>& params): ACommand(params) {}


//erreurs:

	//461 ERR_NEEDMOREPARAMS      // Pas assez de paramètres fournis (canal ou user manquant)
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


//checker si le channel est en mode 
//checker si on est operateur
t_replyHandler	KickCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	(void)target;
	t_replyHandler	replyArray;

	return replyArray;
}
