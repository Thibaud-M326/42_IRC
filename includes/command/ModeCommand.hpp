#ifndef MODECOMMAND_HPP
# define MODECOMMAND_HPP

# include "ACommand.hpp"

class ModeCommand : public ACommand
{
	public:
		ModeCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
