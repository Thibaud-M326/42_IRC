#include "Server.hpp"
#include "Exception.hpp"
#include "Client.hpp"
#include <iostream>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <map>

Server::Server(std::string port, std::string password)
:
	_port(port),
	_password(password),
	_serv_socket_fd(0),
	_serv_sock_addr(),
	_serv_sock_addr_len(sizeof _serv_sock_addr),
	_epoll_fd(0),
	_events(),
	_ev(),
	_client_socket_fd(0),
	_client_sock_addr(),
	_client_sock_addr_len(sizeof _client_sock_addr),
	_nfds(0),
	_buffer(),
	_clients()
{
	std::cout << "Server constructor called" << std::endl;	
}

Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
}

void Server::init_server_socket()
{
	_serv_sock_addr.sin_family = AF_INET;
	_serv_sock_addr.sin_port = htons(PORT);
	_serv_sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	_serv_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_serv_socket_fd == -1)
		throw ExceptionPerror(ERR_MSG);

	if (-1 == set_nonblocking(_serv_socket_fd))
		throw ExceptionPerror(ERR_MSG);

	int opt = 1;
	if (-1 == setsockopt(_serv_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
		throw ExceptionPerror(ERR_MSG);

	if (-1 == bind(_serv_socket_fd, (struct sockaddr *)&_serv_sock_addr, _serv_sock_addr_len))
		throw ExceptionPerror(ERR_MSG);

	if (-1 == listen(_serv_socket_fd, 1))
		throw ExceptionPerror(ERR_MSG);

	std::cout << "The socket server is set and listening" << std::endl;
}

void Server::init_epoll()
{
	_epoll_fd = epoll_create1(0);
	if (_epoll_fd == -1)
		throw ExceptionPerror(ERR_MSG);

	_ev.events = EPOLLIN;
	_ev.data.fd = _serv_socket_fd;

	if (-1 == epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _serv_socket_fd, &_ev))
		throw ExceptionPerror(ERR_MSG);
	
	std::cout << "Server is listening and epoll is set" << '\n';
}

int	Server::set_nonblocking(int sockfd)
{
	int flags = fcntl(sockfd, F_GETFL, 0);
	
    if (flags == -1)
		throw ExceptionPerror(ERR_MSG);

    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1)
		throw ExceptionPerror(ERR_MSG);

    return 0;
}

void	Server::addClientToEpoll()
{
	_ev.events = EPOLLIN | EPOLLET;
	_ev.data.fd = _client_socket_fd;

	if (-1 == epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _client_socket_fd, &_ev))
	{
		close(_client_socket_fd);
		throw ExceptionPerror(ERR_MSG);
	}
}

void	Server::addClient()
{
	int IpAdrress = _client_sock_addr.sin_addr.s_addr;

	Client client(_client_socket_fd, IpAdrress);

	_clients[_client_socket_fd] = client;
}

void	Server::printClients()
{
	std::map<int, Client>::iterator it;

	for (it = _clients.begin(); it != _clients.end(); it++)
	{
		std::cout << it->first << " : " << it->second.getFd() << std::endl;
		std::cout << it->first << " : " << it->second.getIpAddress() << std::endl;
	}
}

void	Server::accept_new_connection()
{
	while (1) 
	{
		_client_socket_fd = accept(_serv_socket_fd, (struct sockaddr *)&_client_sock_addr, &_client_sock_addr_len);

		if (_client_socket_fd == -1)	
		{
			if (errno == EAGAIN)
				break;
			else
				throw ExceptionPerror(ERR_MSG);
		}

		set_nonblocking(_client_socket_fd);

		addClientToEpoll();

		addClient();

		std::cout << "client fd : " << _client_socket_fd << " connected" << std::endl;
	}
}

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

void Server::read_client_paquet(int event_index)
{
	int read_size;

	_client_socket_fd = _events[event_index].data.fd;

	std::cout << "read from client_socket " << _client_socket_fd << " : " << std::endl;

	while(0 < (read_size = read(_client_socket_fd, _buffer, sizeof(_buffer))))
	{
		//process commands
		write(STDOUT_FILENO, _buffer, read_size);
	}

	if (read_size == 0)
	{
		std::cout << "Client " << _client_socket_fd << " disconnected" << std::endl;
		close(_client_socket_fd);
	}
	if (read_size == -1)
	{
		if (errno != EAGAIN)
		{
			close(_client_socket_fd);
			throw ExceptionPerror(ERR_MSG);
		}
	}
}

void Server::run()
{
	while (1)
	{
		_nfds = epoll_wait(_epoll_fd, _events, MAX_EVENT, -1);
		if (_nfds == -1)
			throw ExceptionPerror(ERR_MSG);
		
		for (int i = 0; i < _nfds; i++)
		{
			if (_events[i].data.fd == _serv_socket_fd)
				accept_new_connection();
			else
				read_client_paquet(i);
		}
	}
}
