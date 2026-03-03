#include "FeurBot.hpp"
#include "SignalHandler.hpp"
#include "Parse.hpp"
#include <stdexcept>
#include <iostream>

int	FeurBot::connectToServer()
{
	SignalHandler::initSignal();
	std::string msg;

	if (connect(_socket_fd, (struct sockaddr*)&_sock_addr, sizeof(_sock_addr)) < 0)
		throw std::runtime_error("connect() failed");

	msg = "PASS " + _password + "\r\n";
	if (send(_socket_fd, msg.c_str(), msg.length(), 0) < 0)
		throw std::runtime_error("send() failed: PASS");

	msg = "NICK botbot\r\n";
	if (send(_socket_fd, msg.c_str(), msg.length(), 0) < 0)
		throw std::runtime_error("send() failed: NICK");

	msg = "USER botbot 0 * :botbot\r\n";
	if (send(_socket_fd, msg.c_str(), msg.length(), 0) < 0)
		throw std::runtime_error("send() failed: USER");

	int 		read = 1;
	int 		connected = 0;
	char		buffer[512];
	int			bytes_recv;
	std::string	accumulator;

	while (SignalHandler::isRunning() && read == 1)
	{
		bytes_recv = recv(_socket_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_recv <= 0)
            break;

		buffer[bytes_recv] = '\0';
		accumulator += buffer;
		checkServerConnection(accumulator, read, connected);
	}
	if (connected == 0)
	{
		throw std::runtime_error("can't connect to server Nickname is already in use");
	}
	return 1;
}

void	FeurBot::checkServerConnection(std::string& accumulator, int& read, int& connected)
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

		if (parsedResponse[0].size() == 4
			&& parsedResponse[0][1] == "001")
		{
			connected = 1;
			read = 0;
			break;
		}
		else if (parsedResponse[0][1] == "433")
		{
			connected = 0;
			read = 0;
			break;
		}
	}
}
