#ifndef FEURBOT_HPP
# define FEURBOT_HPP

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string>
# include <vector>
# include <map>
# include <iostream>

#ifndef REPLY
# define REPLY 0
#endif


class FeurBot {

public:
	FeurBot(std::string host, std::string port, std::string password, std::string nick);
	~FeurBot();

	void	runFeurBot();

private:
	void	processReceivedMsg(std::string& accumulator);
	int		processResponse(const std::vector<std::vector<std::string> >& parsedResponse);

	void	sendMsgFromList();
	void	sendFeurReply(const std::vector<std::vector<std::string> >&  parsedResponse);
  void	sendTalkReply(const std::vector<std::vector<std::string> >&  parsedResponse);
	void	connectToChannels();

	int							_socket_fd;
	sockaddr_in					_sock_addr;
	int							_connected;

	std::vector<std::string>	_channelList;
	std::string					_password;
  std::string         _nick;
	std::map<std::string, std::string>	_sendMsgList;

	FeurBot(const FeurBot&);
	FeurBot& operator=(const FeurBot&);
};

#endif
