#ifndef JOINCOMMAND_HPP
# define JOINCOMMAND_HPP

# include "ACommand.hpp"

class JoinCommand : public ACommand
{
	public:
		JoinCommand(std::vector<std::string>& params);
		std::string		ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
