#ifndef REPLY_HPP
# define REPLY_HPP

# include <sstream>
# include "Channel.hpp"
# include "Client.hpp"

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
	inline std::string	WELCOME(Client& target)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 001 "
			<< target.getNickname()
			<< " :Welcome to the Internet Relay Network "
			<< &target.getPrefix()[1] << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	YOURHOST(Client& target)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 002 "
			<< target.getNickname()
			<< " Your host is "
			<< &ircMacro::NAME_SERVER[1]
			<< ", running version " << ircMacro::VERSION
			<< ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	CREATED(Client& target)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 003 "
			<< target.getNickname()
			<< " This server was created "
			<< ircMacro::DATE
			<< " " << &ircMacro::NAME_SERVER[1]
			<< ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	MYINFO(Client& target)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 004 "
			<< target.getNickname()
			<< " " << ircMacro::VERSION
			<< " +" << ircMacro::modeCharArray
			<< ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	BOUNCE(Client& target)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 005 "
			<< target.getNickname()
			<< " NETWORK=" << &ircMacro::NAME_SERVER[1]
			<< " CHANTYPES=" << ircMacro::chanCharArray
			<< " :are supported"
			<< ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	AWAY(Client& source, std::string& away_msg)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 301 "
			<< source.getNickname() << " :"
			<< away_msg << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	NICK(Client& target, std::string& newNickname)
	{
		std::ostringstream	oss;

		oss << target.getPrefix() << " NICK "
			<< newNickname << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	INVITING(Client& target, Channel& chan, std::string invitedNick)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 341 "
			<< target.getNickname() << " "
			<< invitedNick << " "
			<< chan.getName() << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	INVITING_NOTICE(Client& target, Channel& chan, std::string invitedNick)
	{
		std::ostringstream	oss;

		oss <<  target.getPrefix() << "INVITE "
			<< invitedNick << " "
			<< chan.getName() << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	NOTOPIC(Client& target, Channel& chan)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 331 "
			<< target.getNickname() << " "
			<< chan.getName() << " :No topic is set"
			<< ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	TOPIC(Client& target, Channel& chan)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 332 "
			<< target.getNickname() << " "
			<< chan.getName() << " "
			<< chan.getTopic() << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	UMODEIS(Client& target, std::string mode)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 221 "
			<< target.getNickname() << " "
			<<  mode << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	MODE(Client& source, Channel& chan, std::string target)
	{
		std::ostringstream	oss;

		oss << source.getPrefix() << " MODE "
			<< chan.getName()
			<< " +o " << target << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	CHANNELMODEIS(Client& target, Channel& chan)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 324 "
			<< target.getNickname() <<  " " << chan.getName();
		if (!chan.getStrMode().empty())
			oss << " " << chan.getStrMode() << ircMacro::CRLF;
		if (!chan.getModeParams().empty())
			oss << " " << chan.getModeParams() << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	INVITELIST(Client& target, Channel& chan, std::string& invite_list)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 346 "
			<< target.getNickname() << " "
			<< chan.getName() << " "
			<< invite_list << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	ENDOFINVITELIST(Client& target, Channel& chan)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 347 "
			<< target.getNickname() << chan.getName()
			<< " :End of channel invite list"
			<< ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	UNIQOPIS(Client& target, Channel& chan, Client& ope)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 325 "
			<< target.getNickname() << " "
			<< chan.getName() << " "
			<< ope.getUsername() << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	YOUREOPER(Client& target)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 381 "
			<< target.getNickname()
			<< " :You are now an IRC operator"
			<< ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	LIST(Channel& chan, Client& target, size_t count)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 322 "
			<< target.getNickname()
			<< " " << chan.getName()
			<< " " << count << " :"
			<< chan.getTopic() << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	LISTEND(Client& target)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 323 "
			<< target.getNickname()
			<< " :End of /LIST" << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	JOIN(Client& target, std::string chanName, std::string chankey)
	{
		std::ostringstream	oss;

		oss << target.getPrefix() << "JOIN "
			<< chanName;
		if (!chankey.empty())
        	oss << " " << chankey;
		oss << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	PRIVMSG(Client& source, std::string target, std::string msg)
	{
		std::ostringstream	oss;

		oss << source.getPrefix() << "PRIVMSG "
			<< target << " :" << msg << ircMacro::CRLF;
		return oss.str();
	}

	inline	std::string	QUIT(Client& target, std::string msg)
	{
		std::ostringstream	oss;
		
		oss << target.getPrefix() << "QUIT :" << msg << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	KICK(Client& target, std::string chan, std::string user, std::string reason)
	{
		std::ostringstream	oss;

		oss << target.getPrefix() << "KICK "
			<< chan << " " << user;
		if (!reason.empty())
			oss << " " << reason;
		oss << ircMacro::CRLF;
		return oss.str();
	}
	inline std::string	NAMREPLY(Client& target, Channel& chan)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 353 "
			<< target.getNickname() << " = "
			<< chan.getName() << " :"
			<< chan.getClientsStr()
			<< ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	ENDOFNAMES(Client& target, Channel& chan)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 366 "
			<< target.getNickname() << " "
			<< chan.getName() <<
			" :End of /NAMES list" << ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	PART(Client& target, Channel& chan, std::string reason)
	{
		std::ostringstream	oss;

		oss << target.getPrefix() << " PART " << chan.getName();
		if (reason.empty())
			oss << " :Leaving" << ircMacro::CRLF;
		else 
			oss << " " << reason << ircMacro::CRLF;
		return oss.str();
	}
}

namespace ERR 
{
	inline std::string	NOSUCHNICK(Client& target, std::string nickname)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 401 "
			<< target.getNickname() << " "
			<< nickname << " :No such nick/chan"
			<< ircMacro::CRLF;
		return oss.str();
	}

	inline std::string	NOSUCHCHANNEL(Client& target, std::string& chan)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 403 "
			<< target.getNickname() << " "
			<< chan << " :No such channel"
			<< ircMacro::CRLF;
		return oss.str();
	}

	// 405: User has joined too many channels
	inline std::string	TOOMANYCHANNELS(Client& target, Channel& chan)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 405 "
			<< target.getNickname() << " "
			<< chan.getName() <<
			" :You have joined too many channels"
			<< ircMacro::CRLF;
		return oss.str();
	}
	
	// 411: PRIVMSG/NOTICE sent without recipient parameter
	inline std::string	NORECIPIENT(Client& target, std::string command)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 411 "
			<< target.getNickname() <<
			" :No recipient given ("
			<< command << ")" << ircMacro::CRLF;
		return oss.str();
	}

	// 412: PRIVMSG/NOTICE sent without text to send
	inline std::string	NOTEXTTOSEND(Client& target)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 412 "
			<< target.getNickname()
			<< " :No text to send" << ircMacro::CRLF;
		return oss.str();
	}

	// 421: Server received unknown command
	inline std::string	UNKNOWNCOMMAND(Client& target, std::string command)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 421 "
			<< target.getNickname() << " "
			<< command << " :Unknown command"
			<< ircMacro::CRLF;
		return oss.str();
	}

	// 461: Command issued with insufficient parameters
	inline std::string	NEEDMOREPARAMS(Client& target, std::string command)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 461 "
			<< target.getNickname() << " "
			<< command << " :Not enough parameters"
			<< ircMacro::CRLF;
		return oss.str();
	}

	// 462: Command issued before user has fully registered
	inline std::string	ALREADYREGISTRED(Client& target)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 462 "
			<< target.getNickname()
			<< " :Unauthorized command (already registered)"
			<< ircMacro::CRLF;
		return oss.str();
	}

	// 464: Password provided is incorrect
	inline std::string	PASSWDMISMATCH(Client& target)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 464 "
			<< target.getNickname()
			<< " :Password incorrect"
			<< ircMacro::CRLF;
		return oss.str();
	}
	
	// 431: NICK command received with no nickname parameter
	inline std::string	NONICKNAMEGIVEN(Client& target)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 431 "
			<< target.getNickname() <<
			" :No nickname given" << ircMacro::CRLF;
		return oss.str();
	}

	// 432: Nickname contains invalid characters
	inline std::string	ERRONEUSNICKNAME(Client& target, std::string nickname)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 432 "
			<< target.getNickname() << " "
			<< nickname <<
			" :Erroneous nickname" << ircMacro::CRLF;
		return oss.str();
	}

	// 433: Chosen nickname is already in use on server
	inline std::string	NICKNAMEINUSE(Client& target, std::string nickname)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 433 "
			<< target.getNickname() << " "
			<< nickname
			<< " :Nickname is already in use"
			<< ircMacro::CRLF;
		return oss.str();
	}

	// 441: User is not on the specified channel
	inline std::string	USERNOTINCHANNEL(Client& target, Channel& chan, std::string nick_list)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 441 "
			<< target.getNickname() << " "
			<< nick_list << " " << chan.getName()
			<< " :They aren't on that channel"
			<< ircMacro::CRLF;
		return oss.str();
	}

	// 442: Client is not on the specified channel
	inline std::string	NOTONCHANNEL(std::string target, Channel& chan)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 442 "
			<< target << " "
			<< chan.getName()
			<< " :"
			<< target << " is not on that channel"
			<< ircMacro::CRLF;
		return oss.str();
	}

	// 443: User already on channel (e.g., during INVITE)
	inline std::string	USERONCHANNEL(Client& target, Channel& chan, std::string user)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 443 "
			<< target.getNickname() << " " << user
			<< " " << chan.getName()
			<< " :Is already on channel"
			<< ircMacro::CRLF;
		return oss.str();
	}

	// 467: Channel key has already been set
	inline std::string	KEYSET(Client& target, Channel& chan)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 467 "
			<< target.getNickname() << " "
			<< chan.getName()
			<< " :Channel key already set"
			<< ircMacro::CRLF;
		return oss.str();
	}

	// 471: Channel is full (user limit reached)
	inline std::string	CHANNELISFULL(Client& target, Channel& chan)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 471 "
			<< target.getNickname() << " "
			<< chan.getName()
			<< " :Cannot join channel (+l)"
			<< ircMacro::CRLF;
		return oss.str();
	}

	// 472: Unknown channel mode character
	inline std::string	UNKNOWNMODE(Client& target, Channel& chan, char c)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 472 "
			<< target.getNickname() << " " << c
			<< " :is unknown mode char to me for "
			<< chan.getName() << ircMacro::CRLF;
		return oss.str();
	}

	// 473: Cannot join invite-only channel
	inline std::string	INVITEONLYCHAN(Client& target, Channel& chan)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 473 "
			<< target.getNickname() << " "
			<< chan.getName()
			<< " :Cannot join channel (+i)"
			<< ircMacro::CRLF;
		return oss.str();
	}

	// 475: Cannot join channel - bad key provided
	inline std::string	BADCHANNELKEY(Client& target, Channel& chan)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 475 "
			<< target.getNickname() << " "
			<< chan.getName()
			<< " :Cannot join channel (+k)"
			<< ircMacro::CRLF;
		return oss.str();
	}
	// 476: Bad channel Mask
	inline std::string BADCHANMASK(Client& target, std::string channelName)
	{
		std::ostringstream oss;
	
		oss << ircMacro::NAME_SERVER << " 476 "
			<< target.getNickname() << " "
			<< channelName
			<< ":Bad Channel Mask"
			<< ircMacro::CRLF;
		return oss.str();
	}
	// 482: User is not channel operator
	inline std::string	CHANOPRIVSNEEDED(Client& target, Channel& chan)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 482 "
			<< target.getNickname() << " "
			<< chan.getName()
			<< " :You're not channel operator"
			<< ircMacro::CRLF;
		return oss.str();
	}

	// 451: User not yet registered
	inline std::string	NOTREGISTERED(Client& target)
	{
		std::ostringstream	oss;

		oss << ircMacro::NAME_SERVER << " 451 "
			<< target.getNickname()
			<< " :You have not registered"
			<< ircMacro::CRLF;
		return oss.str();
	}
}

#endif
