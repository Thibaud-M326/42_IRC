#ifndef ACOMMAND_HPP
# define ACOMMAND_HPP

# include <vector>
# include "Irc.hpp"

class Client;
class Channel;

class ACommand
{
	protected:
		std::vector<std::string>	_commandArray;
		std::vector<std::string>	_replyArray;

	public:

		ACommand(std::vector<std::string>& params);
		virtual std::vector<std::string>	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray) = 0;
		bool								isSpecialChar(char c) const;

		virtual ~ACommand();

};

#endif
