#ifndef USERCOMMAND_HPP
# define USERCOMMAND_HPP

# include "ACommand.hpp"

class UserCommand : public ACommand
{
	private:
		bool						isValidParams();

	public:
		UserCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
