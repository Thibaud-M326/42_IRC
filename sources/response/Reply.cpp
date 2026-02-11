#include "Client.hpp"
#include "Channel.hpp"

namespace irc_macro
{
	const char CRLF[] = "\r\n";
}
using	irc_macro::CRLF;

namespace reply_code
{
	inline std::string	RPL_WELCOME(Client& target)
	{
		return (target.getPrefix() + " 001 " + target.getPrefix() + CRLF);
	}

	inline std::string	RPL_AWAY(Client& target, std::string& away_msg)
	{
		return (target.getPrefix() + " 301 " + target.getNickname() + " :" + away_msg + CRLF);
	}

	inline std::string	RPL_INVITING(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 341 " + target.getNickname() + " " + chan.getName() + CRLF);
	}

	inline std::string	RPL_NOTOPIC(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 331 " +  chan.getName() + " :No topic is set" + CRLF);
	}

	inline std::string	RPL_TOPIC(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 332 " +  chan.getName() + " :" + chan.getTopic() + CRLF);
	}

	inline std::string	RPL_UMODEIS(Client& target)
	{
		return (target.getPrefix() + " 221 " +  target.get_StrMode() + CRLF);
	}

	inline std::string	RPL_CHANNELMODEIS(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 324 " + chan.getName() + " " + chan.getMode() + " " + chan.getModeParams() + CRLF);
	}

	inline std::string	RPL_INVITELIST(Client& target, Channel& chan, std::string& invite_list)
	{
		return (target.getPrefix() + " 346 " + chan.getName() + " " + invite_list + CRLF);
	}

	inline std::string	RPL_ENDOFINVITELIST(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 347 " + chan.getName() + " :End of channel invite list" + CRLF);
	}

	inline std::string	RPL_UNIQOPIS(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 325 " + chan.getName() + " " + chan.getOperator()->getUsername() + CRLF);
	}

	inline std::string	RPL_YOUREOPER(Client& target)
	{
		return (target.getPrefix() + " 381 :You are now an IRC operator" + CRLF);
	}

	inline std::string	RPL_LIST(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 322 " + chan.getName() + " # visible :" + chan.getTopic() + CRLF);
	}

	inline std::string	RPL_LISTEND(Client& target)
	{
		return (target.getPrefix() + " 323 :End of List" + CRLF);
	}
}

