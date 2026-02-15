#ifndef NICKCOMMAND_HPP
# define NICKCOMMAND_HPP

# include "ACommand.hpp"

class NickCommand : public ACommand
{
	public:
		NickCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);

		bool	isValidNickname(Client& target, mapClients& ClientArray, t_replyHandler& reponseHandler);
};

#endif
