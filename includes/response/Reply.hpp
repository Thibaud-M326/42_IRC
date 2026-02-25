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
		return ("NICK " + target.getNickname() + ircMacro::CRLF);
	}

	inline std::string	USER(Client& target, std::string realName, size_t index)
	{
		std::ostringstream	oss;
		oss << index;
		return ("USER " + target.getUsername() + " " + oss.str() + " * " + realName + ircMacro::CRLF);
	}

	inline std::string	WELCOME(Client& target)
	{
		return ("001 :Welcome to the Internet Relay Network " + target.getPrefix() + ircMacro::CRLF);
	}

	inline std::string	AWAY(Client& source, std::string& away_msg)
	{
		return ("301 " + source.getNickname() + " :" + away_msg + ircMacro::CRLF);
	}

	inline std::string	INVITING(Client& target, Channel& chan)
	{
		return ("341 " + target.getNickname() + " " + chan.getName() + ircMacro::CRLF);
	}

	inline std::string	NOTOPIC(Channel& chan)
	{
		return ("331 " +  chan.getName() + " :No topic is set" + ircMacro::CRLF);
	}

	inline std::string	TOPIC(Channel& chan)
	{
		return ("332 " +  chan.getName() + " :" + chan.getTopic() + ircMacro::CRLF);
	}

	inline std::string	UMODEIS(std::string mode)
	{
		return ("221 " +  mode + ircMacro::CRLF);
	}

	inline std::string	CHANNELMODEIS(Channel& chan)
	{
		return ("324 " + chan.getName() + " " + chan.getStrMode() + " " + chan.getModeParams() + ircMacro::CRLF);
	}

	inline std::string	INVITELIST(Channel& chan, std::string& invite_list)
	{
		return ("346 " + chan.getName() + " " + invite_list + ircMacro::CRLF);
	}

	inline std::string	ENDOFINVITELIST(Channel& chan)
	{
		return ("347 " + chan.getName() + " :End of channel invite list" + ircMacro::CRLF);
	}

	inline std::string	UNIQOPIS(Channel& chan, Client& ope)
	{
		return ("325 " + chan.getName() + " " + ope.getUsername() + ircMacro::CRLF);
	}

	inline std::string	YOUREOPER()
	{
		std::ostringstream	oss;

		oss << "381 :You are now an IRC operator" << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	LIST(Channel& chan)
	{
		return ("322 " + chan.getName() + " # visible :" + chan.getTopic() + ircMacro::CRLF);
	}

	inline std::string	LISTEND()
	{
		std::ostringstream	oss;

		oss << "323 :End of List" << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	JOIN0()
	{
		std::ostringstream	oss;

		oss << "JOIN 0" << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	JOINQUIT(Client& target, std::string chanName)
	{
		return (target.getNickname() + ":Has quit the channel " + chanName + ircMacro::CRLF);
	}

	inline std::string	HASJOIN(Client& target, std::string chanName)
	{
		return (target.getNickname() + " :Has join the channel " + chanName + ircMacro::CRLF);
	}

	inline std::string	JOIN(std::string chanName, std::string chankey)
	{
		std::string msg = "JOIN " + chanName;
		if (!chankey.empty())
        	msg += " " + chankey;
		msg += ircMacro::CRLF;
		return msg;
	}

	inline std::string	PRIVMSG(Client& source, std::string msg)
	{
		return ("PRIVMSG " + source.getNickname() + " :" + msg + ircMacro::CRLF);
	}

	inline	std::string	QUIT(std::string msg)
	{
		return ("QUIT " + msg + ircMacro::CRLF);
	}
}

namespace ERR 
{
	// 401: No such nick/channel
	inline std::string	NOSUCHNICK(std::string nickname)
	{
		return ("401 " + nickname + " :No such nick/chan" + ircMacro::CRLF);
	}

	inline std::string	NOSUCHCHANNEL(std::string& chan)
	{
		return ("403 " + chan + " :No such channel" + ircMacro::CRLF);
	}

	// 405: User has joined too many channels
	inline std::string	TOOMANYCHANNELS(Channel& chan)
	{
		return ("405 " + chan.getName() + " :You have joined too many channels" + ircMacro::CRLF);
	}

	// 407: Too many recipients for PRIVMSG/NOTICE message
	inline std::string	TOOMANYTARGETS(std::string targetChannels)
	{
		return (targetChannels + ":407 recipients." + "Too many recipients" + ircMacro::CRLF);
	}

	// 411: PRIVMSG/NOTICE sent without recipient parameter
	inline std::string	NORECIPIENT(std::string command)
	{
		std::ostringstream	oss;

		oss << "411 " << " :No recipient given (" << command << ")" << ircMacro::CRLF;
		return oss.str();
	}

	// 412: PRIVMSG/NOTICE sent without text to send
	inline std::string	NOTEXTTOSEND(Client& target)
	{
		return ("412 " + target.getNickname() + " :No text to send" + ircMacro::CRLF);
	}

	// 421: Server received unknown command
	inline std::string	UNKNOWNCOMMAND(std::string command)
	{
		return ("421 " + command + " :Unknown command" + ircMacro::CRLF);
	}

	// 461: Command issued with insufficient parameters
	inline std::string	NEEDMOREPARAMS(std::string command)
	{
		return ("461 " + command + " :Not enough parameters" + ircMacro::CRLF);
	}

	// 462: Command issued before user has fully registered
	inline std::string	ALREADYREGISTRED()
	{
		std::ostringstream	oss;

		oss << "462 :Unauthorized command (already registered)" << ircMacro::CRLF;
		return oss.str();
	}

	// 464: Password provided is incorrect
	inline std::string	PASSWDMISMATCH()
	{
		std::ostringstream	oss;

		oss << "464 :Password incorrect" << ircMacro::CRLF;
		return oss.str();
	}

	// 431: NICK command received with no nickname parameter
	inline std::string	NONICKNAMEGIVEN()
	{
		std::ostringstream	oss;

		oss << "431 :No nickname given" << ircMacro::CRLF;
		return oss.str();
	}

	// 432: Nickname contains invalid characters
	inline std::string	ERRONEUSNICKNAME(std::string nickname)
	{
		return ("432 " + nickname + " :Erroneous nickname" + ircMacro::CRLF);
	}

	// 433: Chosen nickname is already in use on server
	inline std::string	NICKNAMEINUSE(std::string nickname)
	{
		return ("433 " + nickname + " :Nickname is already in use" + ircMacro::CRLF);
	}

	// 441: User is not on the specified channel
	inline std::string	USERNOTINCHANNEL(Channel& chan, std::string nick_list)
	{
		return ("441 " + nick_list + " " + chan.getName() + " :They aren't on that channel" + ircMacro::CRLF);
	}

	// 442: Client is not on the specified channel
	inline std::string	NOTONCHANNEL(Channel& chan)
	{
		return ("442 " + chan.getName() + " :You're not on that channel" + ircMacro::CRLF);
	}

	// 443: User already on channel (e.g., during INVITE)
	inline std::string	USERONCHANNEL(Channel& chan, std::string user)
	{
		return ("443 " + user + chan.getName() + " :Is already on channel" + ircMacro::CRLF);
	}

	// 467: Channel key has already been set
	inline std::string	KEYSET(Channel& chan)
	{
		return ("467 " + chan.getName() + " :Channel key already set" + ircMacro::CRLF);
	}

	// 471: Channel is full (user limit reached)
	inline std::string	CHANNELISFULL(Channel& chan)
	{
		return ("471 " + chan.getName() + " :Cannot join channel (+l)" + ircMacro::CRLF);
	}

	// 472: Unknown channel mode character
	inline std::string	UNKNOWNMODE(Channel& chan, char c)
	{
		std::ostringstream	oss;

		oss << "472 " << c << " :is unknown mode char to me for " << chan.getName() << ircMacro::CRLF;
		return oss.str();
	}

	// 473: Cannot join invite-only channel
	inline std::string	INVITEONLYCHAN(Channel& chan)
	{
		return ("473 " + chan.getName() + " :Cannot join channel (+i)" + ircMacro::CRLF);
	}

	// 475: Cannot join channel - bad key provided
	inline std::string	BADCHANNELKEY(Channel& chan)
	{
		return ("475 " + chan.getName() + " :Cannot join channel (+k)" + ircMacro::CRLF);
	}

	// 482: User is not channel operator
	inline std::string	CHANOPRIVSNEEDED(Channel& chan)
	{
		return ("482 " + chan.getName() + " :You're not channel operator" + ircMacro::CRLF);
	}

	// 451: User not yet registered
	inline std::string	NOTREGISTERED()
	{
		std::ostringstream	oss;

		oss << "451 :You have not registered" << ircMacro::CRLF;
		return oss.str();
	}
}

#endif
