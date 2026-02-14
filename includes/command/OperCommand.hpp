#ifndef OPERCOMMAND_HPP
# define OPERCOMMAND_HPP

# include "ACommand.hpp"

class OperCommand : public ACommand
{
	public:
		OperCommand(std::vector<std::string>& params);
		std::string		ExecuteCommand(Client& target, std::map<int, Client*>& ClientArray, std::vector<Channel>& ChannelArray);
};

#endif
