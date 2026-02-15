#ifndef KICKCOMMAND_HPP
# define KICKCOMMAND_HPP

# include "ACommand.hpp"

class KickCommand : public ACommand
{
	public:
		KickCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
