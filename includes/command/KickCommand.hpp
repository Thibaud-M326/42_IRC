#ifndef KICKCOMMAND_HPP
# define KICKCOMMAND_HPP

# include "ACommand.hpp"

class KickCommand : public ACommand
{
	public:
		KickCommand(std::vector<std::string>& params);
		std::string		ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
