#ifndef TOPICCOMMAND_HPP
# define TOPICCOMMAND_HPP

# include "ACommand.hpp"

class TopicCommand : public ACommand
{
	public:
		TopicCommand(std::vector<std::vector<std::string> >& params);
		std::string		ExecuteCommand(std::map<int, Client> ClientArray, std::vector<Channel> ChannelArray);
};

#endif
