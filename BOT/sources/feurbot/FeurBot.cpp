#include "FeurBot.hpp"
#include "Parse.hpp"
#include "SignalHandler.hpp"
#include <stdexcept>
#include <unistd.h>
#include <cstdlib>

FeurBot::FeurBot(std::string host, std::string port, std::string password)
{
	_connected = 0;
	_password = password;

	_sock_addr.sin_family = AF_INET;
	_sock_addr.sin_port = htons(std::atoi(port.c_str()));
	_sock_addr.sin_addr.s_addr = inet_addr(host.c_str());
	if (_sock_addr.sin_addr.s_addr == INADDR_NONE)
		throw std::runtime_error("inet_addr() failed: invalid host");

	_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket_fd < 0)
		throw std::runtime_error("socket() failed");

	if (connect(_socket_fd, (struct sockaddr*)&_sock_addr, sizeof(_sock_addr)) < 0)
		throw std::runtime_error("connect() failed");
	
	std::string	msg = "PASS " + _password + "\r\n" + "NICK botbot\r\n" + "USER botbot 0 * :botbot\r\n";
	std::string action = "connect";

	_sendMsgList.insert(std::make_pair(action, msg));

	msg = "LIST\r\n";
	action = "list";

	_sendMsgList.insert(std::make_pair(action, msg));
}

FeurBot::~FeurBot()
{
	close(_socket_fd);
}

void	FeurBot::sendMsgFromList()
{
	std::map<std::string, std::string>::iterator it;

	it = _sendMsgList.find("connect");

	if (it != _sendMsgList.end()) {
		if (send(_socket_fd, it->second.c_str(), it->second.length(), 0) < 0)
			throw std::runtime_error("send() failed: CONNECT");
		_sendMsgList.erase("connect");
		return;	
	}

	it = _sendMsgList.find("list");

	if (it != _sendMsgList.end()) {
		if (send(_socket_fd, it->second.c_str(), it->second.length(), 0) < 0)
			throw std::runtime_error("send() failed: LIST");
		_sendMsgList.erase("list");
		return;	
	}
}

void	FeurBot::processReceivedMsg(std::string& accumulator)
{
	std::vector<std::vector<std::string> >  parsedResponse;

	size_t pos;
	while ((pos = accumulator.find("\r\n")) != std::string::npos)
	{
		std::string line = accumulator.substr(0, pos + 2);
		accumulator.erase(0, pos + 2);

		if (line.size() > 0 && line[0] == ':')
			line.erase(0, 1);

		Parse parse(line);
		parsedResponse = parse.parseCommand();
		parse.display_vec(parsedResponse);

		processResponse(parsedResponse);
	}
}

int	FeurBot::processResponse(const std::vector<std::vector<std::string> >& parsedResponse)
{
	_sendMsgList.erase("connect");

	if (parsedResponse.size() > 0 && parsedResponse[0].size() == 4 && parsedResponse[0][1] == "001")
		_connected = 1;
	else if (parsedResponse[0][1] == "433")	
		_connected = -1;

	if (_connected)
	{
		if (parsedResponse.size() > 0 && parsedResponse[0].size() > 3
			&& parsedResponse[0][1] == "322")
		{
			std::string chanName = parsedResponse[0][3];
			_channelList.push_back(chanName);
		}
		if (parsedResponse.size() > 0 && parsedResponse[0].size() > 1
			&& parsedResponse[0][1] == "323")
			connectToChannels();
	}

	if (parsedResponse.size() > 0 && parsedResponse[0].size() > 3
		&& parsedResponse[0][1] == "PRIVMSG")
		sendReply(parsedResponse);
	return 0;
}

void	FeurBot::sendReply(const std::vector<std::vector<std::string> >&  parsedResponse)
{
	std::string chanName;
	std::string	privMsg;
	std::string quoiList[] = {"quoi?", "quoi ?", "Quoi?", "Quoi ?", "QUOI?", "QUOI ?", "quoi"};
	size_t 		quoiCount = sizeof(quoiList) / sizeof(quoiList[0]);
	std::string msg;
	size_t 		pos;

	chanName = parsedResponse[0][2];
	privMsg = parsedResponse[0][3];

	for (size_t i = 0; i < quoiCount; i++)
	{
		pos = privMsg.rfind(quoiList[i]);
		if (pos != std::string::npos && (pos + quoiList[i].length() == privMsg.size()))
		{
			if (REPLY == 0)
				msg = "PRIVMSG " + chanName + " :feur!\r\n";
			else
				msg = "PRIVMSG " + chanName + " :quoicoubeh!\r\n";
			if (send(_socket_fd, msg.c_str(), msg.length(), 0) < 0)
				throw std::runtime_error("send() failed: PRIVMSG");
			break;
		}
	}
}

void	FeurBot::connectToChannels()
{
	std::string	msg;

	for (size_t i = 0; i < _channelList.size(); i++)
	{
	    std::cout << "chanlist :" << _channelList[i] << std::endl;

		msg = "JOIN " + _channelList[i] + "\r\n";
		if (send(_socket_fd, msg.c_str(), msg.length(), 0) < 0)
			throw std::runtime_error("send() failed: JOIN " + _channelList[i]);
	}
}

void	FeurBot::runFeurBot()
{
	SignalHandler::initSignal();

	char		buffer[512];
	int			bytes_recv;
	std::string	accumulator;

	while (SignalHandler::isRunning() && _connected != -1)
	{
		if (!_sendMsgList.empty())
			sendMsgFromList();

		bytes_recv = recv(_socket_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_recv <= 0)
            break;

		buffer[bytes_recv] = '\0';
		accumulator += buffer;

		processReceivedMsg(accumulator);
	}
}
