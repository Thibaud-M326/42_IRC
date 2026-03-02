#ifndef INVITECOMMAND_HPP
# define INVITECOMMAND_HPP

# include "ACommand.hpp"

class InviteCommand : public ACommand
{
	private:
		void			addToChannel(Client& target, Channel& channel, t_replyHandler& replyHandler);
	public:
		InviteCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
