#ifndef REPLY_HPP
# define REPLY_HPP

# include "Client.hpp"
# include "Channel.hpp"
# include "Irc.hpp"
# include <vector>
# include <sstream>

namespace RPL
{
	inline std::string	NICK(Client& target)
	{
		return (target.getPrefix() + "NICK " + target.getNickname() + ircMacro::CRLF);
	}

	inline std::string	USER(Client& target, std::string realName, size_t index)
	{
		std::ostringstream	oss;
		oss << index;
		return ("USER " + target.getUsername() + " " + oss.str() + " * " + realName + ircMacro::CRLF);
	}

	inline std::string	WELCOME(Client& target)
	{
		return (target.getPrefix() + "001 " + target.getPrefix() + ircMacro::CRLF);
	}

	inline std::string	AWAY(Client& target, std::string& away_msg)
	{
		return (target.getPrefix() + "301 " + target.getNickname() + " :" + away_msg + ircMacro::CRLF);
	}

	inline std::string	INVITING(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "341 " + target.getNickname() + " " + chan.getName() + ircMacro::CRLF);
	}

	inline std::string	NOTOPIC(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "331 " +  chan.getName() + " :No topic is set" + ircMacro::CRLF);
	}

	inline std::string	TOPIC(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "332 " +  chan.getName() + " :" + chan.getTopic() + ircMacro::CRLF);
	}

	inline std::string	UMODEIS(Client& target)
	{
		return (target.getPrefix() + "221 " +  target.get_StrMode() + ircMacro::CRLF);
	}

	inline std::string	CHANNELMODEIS(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "324 " + chan.getName() + " " + chan.getMode() + " " + chan.getModeParams() + ircMacro::CRLF);
	}

	inline std::string	INVITELIST(Client& target, Channel& chan, std::string& invite_list)
	{
		return (target.getPrefix() + "346 " + chan.getName() + " " + invite_list + ircMacro::CRLF);
	}

	inline std::string	ENDOFINVITELIST(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "347 " + chan.getName() + " :End of channel invite list" + ircMacro::CRLF);
	}

	inline std::string	UNIQOPIS(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "325 " + chan.getName() + " " + chan.getOperator()->getUsername() + ircMacro::CRLF);
	}

	inline std::string	YOUREOPER(Client& target)
	{
		return (target.getPrefix() + "381 :You are now an IRC operator" + ircMacro::CRLF);
	}

	inline std::string	LIST(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "322 " + chan.getName() + " # visible :" + chan.getTopic() + ircMacro::CRLF);
	}

	inline std::string	LISTEND(Client& target)
	{
		return (target.getPrefix() + "323 :End of List" + ircMacro::CRLF);
	}
}

#endif
