#include "Server.hpp"
#include "Exception.hpp"
#include <iostream>
#include <errno.h>
#include <unistd.h>

//pour l'instant j'ecris sur mon stdout des que je recois un control D, control D agit comme le fait d'envoyer le message mais
//je veut en fait ecrire le message uniquement quand j'ai recu un clrf,
//donc je recois mes datas par paquets
//ensuite je stocke les data dans une instance de la classe client,
//quand j'accepte une nouvelle connexion j'ajoute une instance de client a ma client_list
//j'ai ma map de client, a chaque reception de data je dois chercher quelle instance de client c'est en parcourant ma map
//j'ajoute les data au client correspondant en iterant sur les clef de ma client_list,
//lorsque j'ai un message complet, le client me le renvoi et je peut l'afficher, donc quand le client ajoute un nouveau message je check en meme temp
//si un message, ou une suite de message sont complet,

//1 ajouter une instance de client a ma map au momment de l'accept d'un nouveau client
//2 a la reception de data trouver le bon client grace a la map
//3 ajouter au _buffer du client les data
//4 parcourir ce buffer pour trouver un message (termine par clrf)
//5 les message sont stocke dans une map du client_socket; message)
void Server::readClient(int event_index)
{
	int readSize;

	_client_socket_fd = _events[event_index].data.fd;

	// std::cout << "read from client_socket " << _client_socket_fd << " : " << std::endl;

	while(0 < (readSize = read(_client_socket_fd, _buffer, sizeof(_buffer))))
	{
		findClient();

		_client.appendRawData(_buffer, readSize);

		std::cout << "_client.getFd()" << _client.getFd() << "_client.getBuffer() : " << _client.getBuffer() << std::endl;
	}

	//client disconnected
	if (readSize == 0)
	{
		//quand le client se deconnecte, il faut tuer l'instance dans la map
		std::cout << "Client " << _client_socket_fd << " disconnected" << std::endl;
		close(_client_socket_fd);
	}

	//error occured
	if (readSize == -1)
	{
		if (errno != EAGAIN)
		{
			close(_client_socket_fd);
			throw ExceptionPerror(ERR_MSG);
		}
	}
}
