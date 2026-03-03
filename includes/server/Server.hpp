#ifndef SERVER_HPP
# define SERVER_HPP

# include <sys/epoll.h>
# include <netinet/in.h>
# include "Irc.hpp"
# include "Reply.hpp"

class Client;
class Channel;
class ACommand;

class Server {

	private:
		int								_port;
		std::string						_password;

		int								_serv_socket_fd;
		sockaddr_in						_serv_sock_addr;
		socklen_t						_serv_sock_addr_len;

		int								_epoll_fd;
		epoll_event						_events[ircMacro::MAX_EVENT];
		epoll_event						_ev;

		int								_client_socket_fd;
		sockaddr_in						_client_sock_addr;
		socklen_t						_client_sock_addr_len;

		int								_nfds;
		char							_buffer[ircMacro::READ_BUFFER_SIZE];

		Client							*_client;
		std::map<int, Client*>			_clients;
		std::map<std::string, Channel*>	_channelArray;

		std::string						_message;

		int		set_nonblocking(int fd);
		void	acceptConnection();
		void	addClientToEpoll();
		void	addClient();
		void	printClients();
		void	readClient(int event_index);
		void	executeClient(std::string rawCommands);
		void	findClient();
		void	endSafe(const char* err, const char* file, const char* func, int line);
		void	sendToClients(t_replyHandler& replyHandler, ACommand* command);

	public:
		Server(int port, std::string password);
		~Server();

		void	init_server_socket();
		void	init_epoll();
		void	run();
		void	shutDown();
};

#endif
