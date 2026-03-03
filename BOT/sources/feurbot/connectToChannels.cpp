#include "FeurBot.hpp"
#include "Parse.hpp"
#include <iostream>
#include <stdexcept>

void	FeurBot::processListResponse(std::string& accumulator, int& listEnd)
{
	std::vector<std::vector<std::string> >  parsedResponse;

	size_t pos;
	while ((pos = accumulator.find("\r\n")) != std::string::npos)
	{
		std::string line = accumulator.substr(0, pos + 2);
		accumulator.erase(0, pos + 2);
		
		if (line[0] == ':')
			line.erase(0, 1);

		Parse parse(line);
		parsedResponse = parse.parseCommand();
		parse.display_vec(parsedResponse);
		
		if (parsedResponse.size() > 0 && parsedResponse[0].size() > 3
			&& parsedResponse[0][1] == "322")
		{
			std::string chanName = parsedResponse[0][3];
			_channelList.push_back(chanName);
		}
		else if (parsedResponse.size() > 0 && parsedResponse[0].size() > 1
			&& parsedResponse[0][1] == "323")
			listEnd = 1;
	}
}

void	FeurBot::getChannelList()
{
	std::string 							msg;
	char									buffer[512];
	int										bytes_recv;
	std::string 							accumulator;
	int 									listEnd = 0;

	msg = "LIST\r\n";
	if (send(_socket_fd, msg.c_str(), msg.length(), 0) < 0)
		throw std::runtime_error("send() failed: LIST");

	while (!listEnd)
	{
		bytes_recv = recv(_socket_fd, buffer, sizeof(buffer) - 1, 0);
		if (bytes_recv <= 0)
			throw std::runtime_error("recv() failed during LIST");
		buffer[bytes_recv] = '\0';

		accumulator += buffer;

		processListResponse(accumulator, listEnd);
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