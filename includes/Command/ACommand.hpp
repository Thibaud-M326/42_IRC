#ifndef ACOMMAND_HPP
# define ACOMMAND_HPP

# include <vector>
# include <map>
# include "Client.hpp"
# include "Channel.hpp"
# include "Reply.hpp"
# include "Error.hpp"

class ACommand
{
	protected:
		std::vector<std::string>	_CommandArray;
		std::vector<std::string>	_replyArray;

	public:
		ACommand(std::vector<std::string>& params);
		virtual std::string		ExecuteCommand(Client& target, std::map<int, Client>& ClientArray, std::vector<Channel>& ChannelArray) = 0;
		bool					isSpecialChar(char c) const;
		virtual ~ACommand();
};

#endif
