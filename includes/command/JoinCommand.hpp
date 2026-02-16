#ifndef JOINCOMMAND_HPP
# define JOINCOMMAND_HPP

# include "ACommand.hpp"

typedef std::vector<std::pair<std::string, std::string> >	chanParams;

class JoinCommand : public ACommand
{
	private:
		chanParams	buildChannelParams(unsigned int& nbChan);
		bool	isValidChar(char c);
		void	createChannel(mapChannels& ChannelArray, chanParams params);
		void	joinChannel(mapChannels& ChannelArray, chanParams params,
					Client& target, t_replyHandler& replyHandler);

	public:
		JoinCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
