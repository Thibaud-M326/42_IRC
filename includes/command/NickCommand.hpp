#ifndef NICKCOMMAND_HPP
# define NICKCOMMAND_HPP

# include "ACommand.hpp"

class NickCommand : public ACommand
{
	public:
		NickCommand(std::vector<std::string>& params);
		std::vector<std::string>	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);

		void	isValidNickname(Client& target, mapClients& ClientArray);
};

#endif
