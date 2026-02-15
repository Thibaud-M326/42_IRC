#include "Channel.hpp"
#include "Client.hpp"
#include "JoinCommand.hpp"
#include "Reply.hpp"
#include "Irc.hpp"

// - JOIN - Used by a user to request to start listening to the specific channel.
// Note that this message accepts a special argument ("0"), which is a
// special request to leave all channels the user is currently a member of.
// 
// ```ruby
// Parameters: ( \<channel> *( "," \<channel> ) [ \<key> *( "," \<key> ) ] )
//                / "0"
// ```
// 
// - Numeric Replies:
// 
//            ERR_NEEDMOREPARAMS              
//            ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
//            ERR_CHANNELISFULL               ERR_BADCHANMASK
//            ERR_NOSUCHCHANNEL               
//			  RPL_TOPIC

JoinCommand::JoinCommand(std::vector<std::string>& params): ACommand(params) {}

bool	JoinCommand::isValidChar(char c)
{
	for (int i = 0; ircMacro::chanCharArray[i]; i++)
		if (c == ircMacro::chanCharArray[i])
			return true;
	return false;
}

std::vector<std::pair<std::string, std::string> >	JoinCommand::buildChannelParams(unsigned int& nbChan)
{
	std::vector<std::pair<std::string, std::string> >	chanParams;

	for (std::vector<std::string>::iterator word = _commandArray.begin(); word != _commandArray.end(); word++)
	{
		// parse chan name
		for (size_t index = 0; index < word->size(); index++)
		{
			size_t	nextWord = word->find(',', index);
			if (isValidChar((*word)[index]))
			{
				nbChan++;
				if (nextWord == std::string::npos)
				{
					chanParams.push_back(std::make_pair(word->substr(index), ""));
					break ;
				}
				chanParams.push_back(std::make_pair(word->substr(index, nextWord - index), ""));
				index = nextWord;
			}
		}
		// parse chan key
		for (size_t index = 0; index < word->size(); index++)
		{
			if (word == _commandArray.begin())
				break ;
			size_t	nextWord = word->find(',', index);
			if (isValidChar((*word)[index]))
				break ;
			if (nextWord == std::string::npos)
			{
				chanParams.push_back(std::make_pair(word->substr(index), ""));
				break ;
			}
			chanParams.push_back(std::make_pair(word->substr(index, nextWord - index), ""));
			index = nextWord;
		}
	}

	for (size_t i = 0; i < chanParams.size(); i++)
	{
		if (i + nbChan <= chanParams.size())
		{
			chanParams[i].second = chanParams[i + nbChan].first;
			chanParams.erase(chanParams.begin() + (i + nbChan));
		}
	}

	return chanParams;
}

#include <iostream>
t_replyHandler	JoinCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	t_replyHandler	replyHandler;
	unsigned int	nbChan = 0;

	// if (!target.getIsRegistered())
	// {
	// 	replyHandler.add(target.getFd(), ERR::NOTREGISTERED(target));
	// 	return replyHandler;
	// }

	std::vector<std::pair<std::string, std::string> >	chanParams = buildChannelParams(nbChan);

	// for (size_t i = 0; i < chanParams.size(); i++)
	// {
	// 	std::cout << ircMacro::BOLD_BLUE << "|" << ircMacro::BOLD_YELLOW
	// 		<< chanParams[i].first.c_str() << ircMacro::BOLD_BLUE
	// 		<< "|" << ircMacro::BOLD_YELLOW
	// 		<< chanParams[i].second.c_str() << ircMacro::BOLD_BLUE
	// 		<< "|" << ircMacro::STOP_COLOR << '\n';
	// }

	if (chanParams.empty())
	{
		replyHandler.add(target.getFd(), ERR::NEEDMOREPARAMS(target, "JOIN"));
		return replyHandler;
	}

	return replyHandler;
}

