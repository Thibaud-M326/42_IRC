#include <stdexcept>
#include <errno.h>
#include <iostream>
#include "FeurBot.hpp"
#include "Parse.hpp"
#include "SignalHandler.hpp"

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
			msg = "PRIVMSG " + chanName + " :feur!\r\n";
			if (send(_socket_fd, msg.c_str(), msg.length(), 0) < 0)
				throw std::runtime_error("send() failed: PRIVMSG");
			break;
		}
	}
}

void	FeurBot::processRequests(std::string& accumulator)
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

		if (parsedResponse.size() > 0 && parsedResponse[0].size() > 3
			&& parsedResponse[0][1] == "PRIVMSG")
			sendReply(parsedResponse);
	}
}

void	FeurBot::sayFeur()
{
	char									buffer[512];
	int										bytes_recv;
	std::string 							accumulator;


	while (SignalHandler::isRunning())
	{
		bytes_recv = recv(_socket_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_recv <= 0)
            break;

		buffer[bytes_recv] = '\0';
		accumulator += buffer;
		processRequests(accumulator);
	}
}