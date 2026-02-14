#ifndef LISTCOMMAND_HPP
# define LISTCOMMAND_HPP

# include "ACommand.hpp"

class ListCommand : public ACommand
{
	public:
		ListCommand(std::vector<std::string>& params);
		std::vector<std::string>		ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
