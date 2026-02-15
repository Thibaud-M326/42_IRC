#ifndef PASSCOMMAND_HPP
# define PASSCOMMAND_HPP

# include "ACommand.hpp"

class PassCommand : public ACommand
{
	public:
		PassCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
