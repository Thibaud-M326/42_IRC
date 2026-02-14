#ifndef NICKCOMMAND_HPP
# define NICKCOMMAND_HPP

# include "ACommand.hpp"

class NickCommand : public ACommand
{
	public:
		NickCommand(std::vector<std::string>& params);
		std::string	ExecuteCommand(Client& target, std::map<int, Client*>& ClientArray, std::vector<Channel>& ChannelArray);

		std::string	isValidNickname(Client& target, std::map<int, Client*>& ClientArray);
};

#endif
