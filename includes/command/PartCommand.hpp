#ifndef PARTCOMMAND_HPP
# define PARTCOMMAND_HPP

# include "ACommand.hpp"

class PartCommand : public ACommand
{
	private:
		void	eraseChannel(Channel* chan, mapChannels& ChannelArray);

	public:
		PartCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
