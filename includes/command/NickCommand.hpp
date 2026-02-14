#ifndef NICKCOMMAND_HPP
# define NICKCOMMAND_HPP

# include "ACommand.hpp"

class NickCommand : public ACommand
{
	public:
		NickCommand(std::vector<std::string>& params);
		std::string	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);

		std::string	isValidNickname(Client& target, mapClients& ClientArray);
};

#endif
