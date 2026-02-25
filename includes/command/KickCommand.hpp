#ifndef KICKCOMMAND_HPP
# define KICKCOMMAND_HPP

# include "ACommand.hpp"

class KickCommand : public ACommand
{
	public:
		KickCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& source, mapClients& ClientArray, mapChannels& ChannelArray);
		void			kickUsersFromChannel(Client& clientSource, mapClients& ClientArray, mapChannels& ChannelArray, t_replyHandler& replyHandler);
	
	private:
		std::vector<std::string>	splitByComma(std::string argsToSplit);
		bool						isOperator(Client& clientSource, Channel& channel);
		bool						isOperatorOnCanal(Client& clientSource, Channel& channel);
		bool						isUserOnChannel(std::string userName, Channel& channel);
		Client*						getUserOnChannel(std::string userName, Channel& channel);
		void						kickClient(Client& clientToKick, Channel& chan, t_replyHandler& replyHandler);

		std::string					_comments;
};

#endif
