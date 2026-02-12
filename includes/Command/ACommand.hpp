#ifndef ACOMMAND_HPP
# define ACOMMAND_HPP

# include <vector>
# include <map>
# include "Client.hpp"
# include "Channel.hpp"

class ACommand
{
	protected:
		std::vector<std::vector<std::string> >	_CommandArray;

	public:
		ACommand(std::vector<std::vector<std::string> > params);
		virtual std::string		ExecuteCommand(std::map<int, Client> ClientArray, std::vector<Channel> ChannelArray) = 0;
		virtual ~ACommand();
};

#endif
