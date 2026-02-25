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
		bool			isOper(Client& target, Channel& chan);
		void			modeUserLimit(char& signMode, size_t& count, t_replyHandler& replyHandler);
		void			modeOperatorPrivilege(char& signMode, size_t& coun, t_replyHandler& replyHandlert);
		void			modeChannelKey(char& signMode, size_t& count, t_replyHandler& replyHandler);
		void			modeTopicRestriction(char& signMode, size_t& count);
		void			modeInvitOnly(char& signMode, size_t& count);
		void			handleMode(t_replyHandler& replyHandler);

	public:
		ModeCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
