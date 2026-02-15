#ifndef JOINCOMMAND_HPP
# define JOINCOMMAND_HPP

# include "ACommand.hpp"

class JoinCommand : public ACommand
{
	private:
		std::vector<std::pair<std::string, std::string> >	buildChannelParams(unsigned int& nbChan);
		bool												isValidChar(char c);

	public:
		JoinCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
