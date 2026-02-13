#ifndef LISTCOMMAND_HPP
# define LISTCOMMAND_HPP

# include "ACommand.hpp"

class ListCommand : public ACommand
{
	public:
		ListCommand(std::vector<std::string>& params);
		std::string		ExecuteCommand(std::map<int, Client> ClientArray, std::vector<Channel> ChannelArray);
};

#endif
