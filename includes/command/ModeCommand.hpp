#ifndef MODECOMMAND_HPP
# define MODECOMMAND_HPP

# include "ACommand.hpp"

class ModeCommand : public ACommand
{
	public:
		ModeCommand(std::vector<std::string>& params);
		std::string		ExecuteCommand(Client& target, std::map<int, Client*>& ClientArray, std::vector<Channel>& ChannelArray);
};

#endif
