#ifndef QUITCOMMAND_HPP
# define QUITCOMMAND_HPP

# include "ACommand.hpp"

class QuitCommand : public ACommand
{
	public:
		QuitCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
