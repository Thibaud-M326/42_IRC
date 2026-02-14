#ifndef OPERCOMMAND_HPP
# define OPERCOMMAND_HPP

# include "ACommand.hpp"

class OperCommand : public ACommand
{
	public:
		OperCommand(std::vector<std::string>& params);
		std::string		ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
