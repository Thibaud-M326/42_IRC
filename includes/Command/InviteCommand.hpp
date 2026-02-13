#ifndef INVITECOMMAND_HPP
# define INVITECOMMAND_HPP

# include "ACommand.hpp"

class InviteCommand : public ACommand
{
	public:
		InviteCommand(std::vector<std::string>& params);
		std::string		ExecuteCommand(std::map<int, Client> ClientArray, std::vector<Channel> ChannelArray);
};

#endif
