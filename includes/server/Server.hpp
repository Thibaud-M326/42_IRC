#ifndef SERVER_HPP
#define SERVER_HPP

#include "Exception.hpp"
#include "Client.hpp"

#include <string>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <map>
#include <fcntl.h>
#include <unistd.h>

#define MAX_EVENT 10
#define PORT 6667
#define READ_BUFFER_SIZE 1024

//je veut qu'en instanciant un server, mon serveur se mette a ecouter sur le port et le
//mdp qu'on m'a donnee

//la copie de serveur est interdite

//la destruction de mon serveur vas fermer l ecoute et se debarasser de tous les fd enregistre
class Server {

	private:
		std::string _port;
		std::string _password;

		int _serv_socket_fd;
		sockaddr_in _serv_sock_addr;
		socklen_t	_serv_sock_addr_len;
		
		int _epoll_fd;
		epoll_event _events[MAX_EVENT];
		epoll_event _ev;

		int _client_socket_fd;
		sockaddr_in _client_sock_addr;
		socklen_t	_client_sock_addr_len;

		int	_nfds;
		char _buffer[READ_BUFFER_SIZE];

		Client _client;
		std::map<int, Client>	_clients;
		
		int		set_nonblocking(int fd);
		void	acceptConnection();
		void	addClientToEpoll();
		void	addClient();
		void	printClients();
		void	readClient(int event_index);
		void	processClient();

	public :
		Server(std::string port, std::string password);
		~Server();

		void	init_server_socket();
		void	init_epoll();
		void	run();

};

#endif