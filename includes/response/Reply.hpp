#ifndef REPLY_HPP
# define REPLY_HPP

# include "Client.hpp"
# include "Channel.hpp"
# include "Irc.hpp"
# include <sstream>

#include <iostream>

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
		std::cout << "haaaaaaaaaaaaaa" << std::endl;
		t_outGoingMessages	msg;

		msg.targets.push_back(fd);
		msg.reply = rep;
		messages.push_back(msg);
	};

	inline void	add(std::vector<int> fds, const std::string& rep)
	{
		t_outGoingMessages	msg;

		std::cout << "heuuuuuuuuuu" << std::endl;

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

	inline std::string	AWAY(Client& source, std::string& away_msg)
	{
		return (source.getPrefix() + "301 " + source.getNickname() + " :" + away_msg + ircMacro::CRLF);
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
		std::string msg = target.getPrefix() + "JOIN " + chanName;
		if (!chankey.empty())
        	msg += " " + chankey;
		msg += ircMacro::CRLF;
		return msg;
	}

	inline std::string	PRIVMSG(Client& source, std::string target, std::string msg)
	{
		return (source.getPrefix() + "PRIVMSG " + target + " :" + msg + ircMacro::CRLF);
	}
}

namespace ERR 
{
	// 401: No such nick/channel
	inline std::string	NOSUCHNICK(Client& target, std::string nickname)
	{
		return (target.getPrefix() + "401 " + nickname + " :No such nick/chan" + ircMacro::CRLF);
	}

	inline std::string	NOSUCHCHANNEL(Client& target, std::string& chan)
	{
		return (target.getPrefix() + "403 " + chan + " :No such channel" + ircMacro::CRLF);
	}

	// 405: User has joined too many channels
	inline std::string	TOOMANYCHANNELS(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "405 " + chan.getName() + " :You have joined too many channels" + ircMacro::CRLF);
	}

	// 407: Too many recipients for PRIVMSG/NOTICE message
	inline std::string	TOOMANYTARGETS(Client& target, std::string targetChannels)
	{
		return (target.getPrefix() + targetChannels + ":407 recipients." + "Too many recipients" + ircMacro::CRLF);
	}

	// 411: PRIVMSG/NOTICE sent without recipient parameter
	inline std::string	NORECIPIENT(Client& target, std::string command)
	{
		return (target.getPrefix() + "411 :No recipient given (" + command + ")" + ircMacro::CRLF);
	}

	// 412: PRIVMSG/NOTICE sent without text to send
	inline std::string	NOTEXTTOSEND(Client& target)
	{
		return (target.getPrefix() + "412 :No text to send" + ircMacro::CRLF);
	}

	// 421: Server received unknown command
	inline std::string	UNKNOWNCOMMAND(Client& target, std::string command)
	{
		return (target.getPrefix() + "421 " + command + " :Unknown command" + ircMacro::CRLF);
	}

	// 461: Command issued with insufficient parameters
	inline std::string	NEEDMOREPARAMS(Client& target, std::string command)
	{
		return (target.getPrefix() + "461 " + command + " :Not enough parameters" + ircMacro::CRLF);
	}

	// 462: Command issued before user has fully registered
	inline std::string	ALREADYREGISTRED(Client& target)
	{
		return (target.getPrefix() + "462 :Unauthorized command (already registered)" + ircMacro::CRLF);
	}

	// 464: Password provided is incorrect
	inline std::string	PASSWDMISMATCH(Client& target)
	{
		return (target.getPrefix() + "464 :Password incorrect" + ircMacro::CRLF);
	}

	// 431: NICK command received with no nickname parameter
	inline std::string	NONICKNAMEGIVEN(Client& target)
	{
		return (target.getPrefix() + "431 :No nickname given" + ircMacro::CRLF);
	}

	// 432: Nickname contains invalid characters
	inline std::string	ERRONEUSNICKNAME(Client& target, std::string nickname)
	{
		return (target.getPrefix() + "432 " + nickname + " :Erroneous nickname" + ircMacro::CRLF);
	}

	// 433: Chosen nickname is already in use on server
	inline std::string	NICKNAMEINUSE(Client& target, std::string nickname)
	{
		return (target.getPrefix() + "433 " + nickname + " :Nickname is already in use" + ircMacro::CRLF);
	}

	// 441: User is not on the specified channel
	inline std::string	USERNOTINCHANNEL(Client& target, Channel& chan, std::string nick_list)
	{
		return (target.getPrefix() + "441 " + nick_list + " " + chan.getName() + " :They aren't on that channel" + ircMacro::CRLF);
	}

	// 442: Client is not on the specified channel
	inline std::string	NOTONCHANNEL(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "442 " + chan.getName() + " :You're not on that channel" + ircMacro::CRLF);
	}

	// 443: User already on channel (e.g., during INVITE)
	inline std::string	USERONCHANNEL(Client& target, Channel& chan, std::string user)
	{
		return (target.getPrefix() + "443 " + user + chan.getName() + " :Is already on channel" + ircMacro::CRLF);
	}

	// 467: Channel key has already been set
	inline std::string	KEYSET(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "467 " + chan.getName() + " :Channel key already set" + ircMacro::CRLF);
	}

	// 471: Channel is full (user limit reached)
	inline std::string	CHANNELISFULL(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "471 " + chan.getName() + " :Cannot join channel (+l)" + ircMacro::CRLF);
	}

	// 472: Unknown channel mode character
	inline std::string	UNKNOWNMODE(Client& target, Channel& chan, char c)
	{
		return (target.getPrefix() + "472 " + c + " :is unknown mode char to me for " + chan.getName() + ircMacro::CRLF);
	}

	// 473: Cannot join invite-only channel
	inline std::string	INVITEONLYCHAN(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "473 " + chan.getName() + " :Cannot join channel (+i)" + ircMacro::CRLF);
	}

	// 475: Cannot join channel - bad key provided
	inline std::string	BADCHANNELKEY(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "475 " + chan.getName() + " :Cannot join channel (+k)" + ircMacro::CRLF);
	}

	// 482: User is not channel operator
	inline std::string	CHANOPRIVSNEEDED(Client& target, Channel& chan)
	{
		return (target.getPrefix() + "482 " + chan.getName() + " :You're not channel operator" + ircMacro::CRLF);
	}

	// 501: Invalid MODE flag provided by user
	inline std::string	UMODEUNKNOWNFLAG(Client& target)
	{
		return (target.getPrefix() + "501 :Unknown MODE flag" + ircMacro::CRLF);
	}
	// 451: User not yet registered
	inline std::string	NOTREGISTERED(Client& target)
	{
		return (target.getPrefix() + "451 :You have not registered" + ircMacro::CRLF);
	}
}

#endif
