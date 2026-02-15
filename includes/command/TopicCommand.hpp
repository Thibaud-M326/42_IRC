#ifndef TOPICCOMMAND_HPP
# define TOPICCOMMAND_HPP

# include "ACommand.hpp"

class TopicCommand : public ACommand
{
	public:
		TopicCommand(std::vector<std::string>& params);
		t_replyHandler	ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray);
};

#endif
