#include "Channel.hpp"
#include "Client.hpp"
#include "JoinCommand.hpp"
#include "Reply.hpp"
#include "Error.hpp"

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
//            ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
//			  RPL_TOPIC

JoinCommand::JoinCommand(std::vector<std::string>& params): ACommand(params) {}

std::vector<std::string>	JoinCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	// if (!target.getIsRegistered())
	// 	return ERR::NOTREGISTERED(target);
	(void)target;
	(void)ClientArray;
	(void)ChannelArray;
	return _replyArray;
}

