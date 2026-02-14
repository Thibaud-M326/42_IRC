#ifndef USERCOMMAND_HPP
# define USERCOMMAND_HPP

# include "ACommand.hpp"

class UserCommand : public ACommand
{
	public:
		UserCommand(std::vector<std::string>& params);
		std::vector<std::string>	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
		bool						isValidParams();
};

#endif
