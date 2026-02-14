#ifndef ACOMMAND_HPP
# define ACOMMAND_HPP

# include <vector>
# include "Irc.hpp"

class Client;
class Channel;

class ACommand
{
	protected:
		std::vector<std::string>	_CommandArray;

	public:

		ACommand(std::vector<std::string>& params);
		virtual std::string	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray) = 0;
		bool				isSpecialChar(char c) const;

		virtual ~ACommand();

};

#endif
