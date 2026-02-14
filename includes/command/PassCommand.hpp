#ifndef PASSCOMMAND_HPP
# define PASSCOMMAND_HPP

# include "ACommand.hpp"

class PassCommand : public ACommand
{
	public:
		PassCommand(std::vector<std::string>& params);
		std::string		ExecuteCommand(Client& target, std::map<int, Client*>& ClientArray, std::vector<Channel>& ChannelArray);
};

#endif
