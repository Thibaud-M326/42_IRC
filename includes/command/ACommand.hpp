#ifndef ACOMMAND_HPP
# define ACOMMAND_HPP

# include <vector>
# include "Irc.hpp"
# include "Reply.hpp"

class Client;
class Channel;

class ACommand
{
	protected:
		std::vector<std::string>	_commandArray;

	public:

		ACommand(std::vector<std::string>& params);

		virtual t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray) = 0;
		bool					isSpecialChar(char c) const;
		bool					isValidChar(char c) const;
		Channel*				getChannelByName(std::string chan, mapChannels& ChannelArray) const;
		Client*					findClientByNickName(std::string nickname, mapClients& ClientArray) const;
		bool					channelExist(std::string channelName, mapChannels& ChannelArray);

		virtual ~ACommand();

};

#endif
