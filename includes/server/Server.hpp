#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/epoll.h>
#include <netinet/in.h>
#include <sys/socket.h>

namespace server 
{
	extern const int MAX_EVENT;
}

//je veut qu'en instanciant un server, mon serveur se mette a ecouter sur le port et le
//mdp qu'on m'a donnee

//la copie de serveur est interdite

//la destruction de mon serveur vas fermer l ecoute et se debarasser de tous les fd enregistre
class Server {

	private:
		std::string _port;
		std::string _password;

		int _serv_socket;
		int _client_socket;
		int _epoll_fd;
		int _nfds;
		epoll_event _events[MAX_EVENT];
		epoll_event _ev;
		sockaddr_in _addr;

	public :
		Server(std::string port, std::string password);
		~Server();

};

#endif