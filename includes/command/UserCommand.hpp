#ifndef USERCOMMAND_HPP
# define USERCOMMAND_HPP

# include "ACommand.hpp"

class UserCommand : public ACommand
{
	public:
		UserCommand(std::vector<std::string>& params);
		std::string		ExecuteCommand(Client& target, std::map<int, Client*>& ClientArray, std::vector<Channel>& ChannelArray);
		bool			isValidParams();
};

#endif
