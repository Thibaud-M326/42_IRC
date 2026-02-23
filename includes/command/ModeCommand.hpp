#ifndef MODECOMMAND_HPP
# define MODECOMMAND_HPP

# include "ACommand.hpp"

class ModeCommand : public ACommand
{
	private:
		char			isValidFlag(char c);
		char			verifFlag();
		bool			isOper(Client& target, Channel& chan);

	public:
		ModeCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
