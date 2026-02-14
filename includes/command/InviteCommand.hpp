#ifndef INVITECOMMAND_HPP
# define INVITECOMMAND_HPP

# include "ACommand.hpp"

class InviteCommand : public ACommand
{
	public:
		InviteCommand(std::vector<std::string>& params);
		std::vector<std::string>	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
