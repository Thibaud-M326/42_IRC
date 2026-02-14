#ifndef JOINCOMMAND_HPP
# define JOINCOMMAND_HPP

# include "ACommand.hpp"

class JoinCommand : public ACommand
{
	public:
		JoinCommand(std::vector<std::string>& params);
		std::string		ExecuteCommand(Client& target, std::map<int, Client*>& ClientArray, std::vector<Channel>& ChannelArray);
};

#endif
