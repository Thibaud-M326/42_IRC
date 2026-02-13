#ifndef ACOMMAND_HPP
# define ACOMMAND_HPP

# include <vector>
# include <map>
# include "Client.hpp"
# include "Channel.hpp"
# include "Reply.hpp"

namespace MacroCommand
{
	extern const int	SUCCESS;
}

class ACommand
{
	protected:
		std::vector<std::string>	_CommandArray;

	public:
		ACommand(std::vector<std::string>& params);
		virtual std::string		ExecuteCommand(Client& target, std::map<int, Client>& ClientArray, std::vector<Channel>& ChannelArray) = 0;
		virtual ~ACommand();
};

#endif
