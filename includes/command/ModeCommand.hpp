#ifndef MODECOMMAND_HPP
# define MODECOMMAND_HPP

# include "ACommand.hpp"

class ModeCommand : public ACommand
{
	private:
		Channel			*_channel;
		Client			_client;

		char			isValidFlag(char mode);
		char			verifFlag();
		void			modeUserLimit(Client& target, char& signMode, size_t& count, t_replyHandler& replyHandler);
		void			modeOperatorPrivilege(Client& clientSource, char& signMode, size_t& coun, t_replyHandler& replyHandlert);
		void			modeChannelKey(Client& target, char& signMode, size_t& count, t_replyHandler& replyHandler);
		void			modeTopicRestriction(char& signMode, size_t& count);
		void			modeInvitOnly(char& signMode, size_t& count);
		void			handleMode(Client& target, t_replyHandler& replyHandler);

	public:
		ModeCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
