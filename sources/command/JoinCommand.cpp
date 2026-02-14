#include "JoinCommand.hpp"

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
//            ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
//            ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
//            ERR_CHANNELISFULL               ERR_BADCHANMASK
//            ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
//            ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
// 		   RPL_TOPIC


JoinCommand::JoinCommand(std::vector<std::string>& params): ACommand(params) {}

std::string	JoinCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray)
{
	(void)ClientArray;
	(void)ChannelArray;
	(void)target;
	return ("");
}

