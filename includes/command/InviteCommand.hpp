#ifndef INVITECOMMAND_HPP
# define INVITECOMMAND_HPP

# include "ACommand.hpp"

class InviteCommand : public ACommand
{
	public:
		InviteCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
