#ifndef REPLY_HPP
# define REPLY_HPP

# include "Client.hpp"
# include "Channel.hpp"
# include "Irc.hpp"
# include <sstream>

typedef struct s_outGoingMessages
{
	std::vector<int>				targets;
	std::string						reply;
}	t_outGoingMessages;

typedef struct s_replyHandler
{
	std::vector<t_outGoingMessages>	messages;

	inline void	add(int fd, const std::string& rep)
	{
		t_outGoingMessages	msg;

		msg.targets.push_back(fd);
		msg.reply = rep;
		messages.push_back(msg);
	};

	inline void	add(std::vector<int> fds, const std::string& rep)
	{
		t_outGoingMessages	msg;

		msg.targets = fds;
		msg.reply = rep;
		messages.push_back(msg);
	};

}	t_replyHandler;

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
		return (target.getPrefix() + "221 " +  target.getStrMode() + ircMacro::CRLF);
	}

	inline std::string	CHANNELMODEIS(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "324 " + chan.getName() + " " + chan.getStrMode() + " " + chan.getModeParams() + ircMacro::CRLF);
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

	inline std::string	JOIN0(Client& target)
	{
		return (target.getPrefix() + "JOIN 0" + ircMacro::CRLF);
	}

	inline std::string	JOINQUIT(Client& target, std::string chanName)
	{
		return (target.getPrefix() + ":Has quit the channel " + chanName + ircMacro::CRLF);
	}

	inline std::string	JOIN(Client& target, std::string chanName, std::string chankey)
	{
		return (target.getPrefix() + "JOIN " + chanName + chankey);
	}
}

namespace ERR 
{
	inline std::string	NOSUCHNICK(Client& target)
	{
		return (target.getPrefix() + "401 " + target.getNickname() + " :No such nick/chan" + ircMacro::CRLF);
	}

	inline std::string	NOSUCHCHANNEL(Client& target, std::string& chan)
	{
		return (target.getPrefix() + "403 " + chan + " :No such channel" + ircMacro::CRLF);
	}

	inline std::string	TOOMANYCHANNELS(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "405 " + chan.getName() + " :You have joined too many channels" + ircMacro::CRLF);
	}

	inline std::string	NORECIPIENT(Client& target, std::string command)
	{
		return (target.getPrefix() + "411 :No recipient given (" + command + ")" + ircMacro::CRLF);
	}

	inline std::string	NOTEXTTOSEND(Client& target)
	{
		return (target.getPrefix() + "412 :No text to send" + ircMacro::CRLF);
	}

	inline std::string	UNKNOWNCOMMAND(Client& target, std::string command)
	{
		return (target.getPrefix() + "421 " + command + " :Unknown command" + ircMacro::CRLF);
	}

	inline std::string	NEEDMOREPARAMS(Client& target, std::string command)
	{
		return (target.getPrefix() + "461 " + command + " :Not enough parameters" + ircMacro::CRLF);
	}

	inline std::string	ALREADYREGISTRED(Client& target)
	{
		return (target.getPrefix() + "462 :Unauthorized command (already registered)" + ircMacro::CRLF);
	}

	inline std::string	PASSWDMISMATCH(Client& target)
	{
		return (target.getPrefix() + "464 :Password incorrect" + ircMacro::CRLF);
	}

	inline std::string	NONICKNAMEGIVEN(Client& target)
	{
		return (target.getPrefix() + "431 :No nickname given" + ircMacro::CRLF);
	}

	inline std::string	ERRONEUSNICKNAME(Client& target, std::string nickname)
	{
		return (target.getPrefix() + "432 " + nickname + " :Erroneous nickname" + ircMacro::CRLF);
	}

	inline std::string	NICKNAMEINUSE(Client& target, std::string nickname)
	{
		return (target.getPrefix() + "433 " + nickname + " :Nickname is already in use" + ircMacro::CRLF);
	}

	inline std::string	USERNOTINCHANNEL(Client& target, Channel& chan, std::string nick_list)
	{
		return (target.getPrefix() + "441 " + nick_list + " " + chan.getName() + " :They aren't on that channel" + ircMacro::CRLF);
	}

	inline std::string	NOTONCHANNEL(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "442 " + chan.getName() + " :You're not on that channel" + ircMacro::CRLF);
	}

	inline std::string	USERONCHANNEL(Client& target, Channel& chan, std::string user)
	{
		return (target.getPrefix() + "443 " + user + chan.getName() + " :Is already on channel" + ircMacro::CRLF);
	}

	inline std::string	KEYSET(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "467 " + chan.getName() + " :Channel key already set" + ircMacro::CRLF);
	}

	inline std::string	CHANNELISFULL(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "471 " + chan.getName() + " :Cannot join channel (+l)" + ircMacro::CRLF);
	}

	inline std::string	UNKNOWNMODE(Client& target, Channel& chan, char c)
	{
		return (target.getPrefix() + "472 " + c + " :is unknown mode char to me for " + chan.getName() + ircMacro::CRLF);
	}

	inline std::string	INVITEONLYCHAN(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "473 " + chan.getName() + " :Cannot join channel (+i)" + ircMacro::CRLF);
	}

	inline std::string	BADCHANNELKEY(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "475 " + chan.getName() + " :Cannot join channel (+k)" + ircMacro::CRLF);
	}

	inline std::string	CHANOPRIVSNEEDED(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "482 " + chan.getName() + " :You're not channel operator" + ircMacro::CRLF);
	}

	inline std::string	UMODEUNKNOWNFLAG(Client& target)
	{
		return (target.getPrefix() + "501 :Unknown MODE flag" + ircMacro::CRLF);
	}
	inline std::string	NOTREGISTERED(Client& target)
	{
		return (target.getPrefix() + "451 :You have not registered" + ircMacro::CRLF);
	}
}

#endif
