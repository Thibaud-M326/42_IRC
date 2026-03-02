#ifndef ACOMMAND_HPP
# define ACOMMAND_HPP

# include "Reply.hpp"

class Client;
class Channel;

class ACommand
{
	protected:
		std::vector<std::string>	_commandArray;

		bool					isSpecialChar(char c) const;
		bool					isValidChar(char c) const;
		Channel*				getChannelByName(std::string chan, mapChannels& ChannelArray) const;
		Client*					findClientByNickName(std::string nickname, std::vector<Client*> ClientArray) const;
		bool					isOper(Client& target, Channel& chan);
		std::vector<Client*>	buildClientVec(mapClients& ClientArray) const;

	public:
		ACommand(std::vector<std::string>& params);
		virtual ~ACommand();

		virtual t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray) = 0;

};

#endif
