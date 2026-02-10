#include "Server.hpp"

#include <iostream>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


//init server value to zero
Server::Server(std::string port, std::string password)
:
	_port(port),
	_password(password),
	_serv_socket_fd(0),
	_epoll_fd(0),
	_nfds(0),
	_events(),
	_ev(),
	_serv_sock_addr(),
	_serv_sock_addr_len(sizeof _serv_sock_addr),
	_client_socket_fd(0),
	_client_sock_addr(),
	_client_sock_addr_len(sizeof _client_sock_addr),
	_buffer()
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
		;;;;

	if (-1 == set_nonblocking(_serv_socket_fd))
		;;;;

	int opt = 1;
	if (-1 == setsockopt(_serv_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
		;;;;

	if (-1 == bind(_serv_socket_fd, (struct sockaddr *)&_serv_sock_addr, _serv_sock_addr_len))
		;;;;

	if (-1 == listen(_serv_socket_fd, 1))
		;;;;

	std::cout << "The socket server is set and listening" << std::endl;
}

int	Server::set_nonblocking(int sockfd)
{
	int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        //perror("fcntl(F_GETFL)");
        return -1;
    }
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        //perror("fcntl(F_SETFL)");
        return -1;
    }
    return 0;
}

void Server::init_epoll()
{
	_epoll_fd = epoll_create1(0);
	if (_epoll_fd == -1)
		;;;;

	_ev.events = EPOLLIN;
	_ev.data.fd = _serv_socket_fd;

	if (-1 == epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _serv_socket_fd, &_ev))
		;;;;
	
	std::cout << "Server is listening and epoll is set" << '\n';
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
				;;;; // break
		}

		if (-1 == set_nonblocking(_serv_socket_fd))
			;;;; //break

		_ev.events = EPOLLIN | EPOLLET;
		_ev.data.fd = _client_socket_fd;

		if (-1 == epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _client_socket_fd, &_ev))
		{
			close(_client_socket_fd);
			;;;; //break
		}
	}
}

void Server::read_client_paquet(int event_index)
{
	int read_size;

	_client_socket_fd = _events[event_index].data.fd;

	while(0 < (read_size = read(_client_socket_fd, _buffer, sizeof(_buffer))))
	{
		//process commands
		write(STDOUT_FILENO, _buffer, read_size);
	}

	if (read_size == 0)
	{
		std::cout << "Client" << _client_socket_fd << "disconnected" << std::endl;
		close(_client_socket_fd);
	}
	if (read_size == -1)
	{
		if (errno != EAGAIN)
		{
			close(_client_socket_fd);
			;;;; //read error //throw ??
		}
	}
}

//represente la boucle de epoll
//epoll va devoir ecouter les evenenement
//il va retourner une liste des evenements
//il va devoir attribuer la string totale a chacune des instance de client
//dans le container (socket; client());
//a chaque reception d evenement on recois une quantite des bits du messagee
//les bits ne sont pas forcement tous recu au moment ou l'evenement est declenche
//donc lorsqu'un evenement est lance, on vas devoir enregistrer le bout de donne recu
//dans le bon client grace a son socket dans le container
//et tant qu'on recois pas \r\n je ne peut pas considerer que la string est complete
//je dois donc - 
//enregistrer la string dans le bon client
//verifier si on a atteint un \r\n
//si oui on doit couper la string jusquá \r\n et laisser ce qu'il y a ensuite de cote
//en sauvegarde, nouvelle base de la string qui sera le prochain message
//
//si j'ai recu un message en entier, alors je doit executer la commande
//
//attention : 
//un seul read peut contenir plusieurs commandes aussi !!
void Server::run()
{
	while (1)
	{
		_nfds = epoll_wait(_epoll_fd, _events, MAX_EVENT, -1);
		if (_nfds == -1)
			;;;;//break erreur bloquante
		
		for (int i = 0; i < _nfds; i++)
		{
			//event on server socket
			if (_events[i].data.fd == _serv_socket_fd)
				accept_new_connection();
			else
				read_client_paquet(i);
		}
	}
}
