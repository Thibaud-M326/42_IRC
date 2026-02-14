#ifndef PRIVMSGCOMMAND_HPP
# define PRIVMSGCOMMAND_HPP

# include "ACommand.hpp"

class PrivMsgCommand : public ACommand
{
	public:
		PrivMsgCommand(std::vector<std::string>& params);
		std::string		ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
