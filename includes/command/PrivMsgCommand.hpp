#ifndef PRIVMSGCOMMAND_HPP
# define PRIVMSGCOMMAND_HPP

# include "ACommand.hpp"

class PrivMsgCommand : public ACommand
{
	public:
		PrivMsgCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& clientSource, mapClients& ClientArray, mapChannels& ChannelArray);

		bool	isValidPrivMsg(Client& clientSource, mapClients& ClientArray, t_replyHandler& replyHandler);
		t_replyHandler	sendPrivMsgToNickname(Client& clientSource, mapClients& ClientArray, t_replyHandler& replyHandler);

};

#endif
