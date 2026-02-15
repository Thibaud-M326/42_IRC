#ifndef OPERCOMMAND_HPP
# define OPERCOMMAND_HPP

# include "ACommand.hpp"

class OperCommand : public ACommand
{
	public:
		OperCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
