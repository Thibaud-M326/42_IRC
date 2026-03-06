#ifndef FEURBOT_HPP
#define FEURBOT_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <vector>
#include <map>

class FeurBot {

	private:

		FeurBot(const FeurBot&);
		FeurBot& operator=(const FeurBot&);

		void	sendReply(const std::vector<std::vector<std::string> >&  parsedResponse);
		void	processRequests(std::string& accumulator);
		void	processListResponse(std::string& accumulator, int& listEnd);
		void	processReceivedMsg(std::string& accumulator);

		void	sendMsgFromList();
		int		processResponse(const std::vector<std::vector<std::string> >& parsedResponse);

		int							_socket_fd;
		sockaddr_in					_sock_addr;
		std::vector<std::string>	_channelList;
		std::string					_password;

		int							_connected;

		std::map<std::string, std::string>	_sendMsgList;

	public:

		FeurBot(std::string host, std::string port, std::string password);
		~FeurBot();

		int 	connectToServer();
		void	getChannelList();
		void	connectToChannels();
		void	sayFeur();

		void	runFeurBot();
};

#endif
