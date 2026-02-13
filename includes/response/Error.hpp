#ifndef ERROR_HPP
# define ERROR_HPP

# include "Channel.hpp"
# include "Client.hpp"
# include "Irc.hpp"

namespace ERR 
{
	inline std::string	NOSUCHNICK(Client& target)
	{
		return (target.getPrefix() + " 401 " + target.getNickname() + " :No such nick/chan" + CRLF);
	}

	inline std::string	NOSUCHCHANNEL(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 403 " + chan.getName() + " :No such channel" + CRLF);
	}

	inline std::string	TOOMANYCHANNELS(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 405 " + chan.getName() + " :You have joined too many channels" + CRLF);
	}

	inline std::string	NORECIPIENT(Client& target, std::string command)
	{
		return (target.getPrefix() + " 411 :No recipient given (" + command + ")" + CRLF);
	}

	inline std::string	NOTEXTTOSEND(Client& target)
	{
		return (target.getPrefix() + " 412 :No text to send" + CRLF);
	}

	inline std::string	UNKNOWNCOMMAND(Client& target, std::string command)
	{
		return (target.getPrefix() + " 421 " + command + " :Unknown command" + CRLF);
	}

	inline std::string	NEEDMOREPARAMS(Client& target, std::string command)
	{
		return (target.getPrefix() + " 461 " + command + " :Not enough parameters" + CRLF);
	}

	inline std::string	ALREADYREGISTERED(Client& target)
	{
		return (target.getPrefix() + " 462 :Unauthorized command (already registered)" + CRLF);
	}

	inline std::string	PASSWDMISMATCH(Client& target)
	{
		return (target.getPrefix() + " 464 :Password incorrect" + CRLF);
	}

	inline std::string	NONICKNAMEGIVEN(Client& target)
	{
		return (target.getPrefix() + " 431 :No nickname given" + CRLF);
	}

	inline std::string	ERRONEUSNICKNAME(Client& target, std::string nickname)
	{
		return (target.getPrefix() + " 432 " + nickname + " :Erroneous nickname" + CRLF);
	}

	inline std::string	NICKNAMEINUSE(Client& target, std::string nickname)
	{
		return (target.getPrefix() + " 433 " + nickname + " :Nickaname is already in use" + CRLF);
	}

	inline std::string	USERNOTINCHANNEL(Client& target, Channel& chan, std::string nick_list)
	{
		return (target.getPrefix() + " 441 " + nick_list + " " + chan.getName() + " :They aren't on that channel" + CRLF);
	}

	inline std::string	NOTONCHANNEL(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 442 " + chan.getName() + " :You're not on that channel" + CRLF);
	}

	inline std::string	USERONCHANNEL(Client& target, Channel& chan, std::string user)
	{
		return (target.getPrefix() + " 443 " + user + chan.getName() + " :Is already on channel" + CRLF);
	}

	inline std::string	KEYSET(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 467 " + chan.getName() + " :Channel key already set" + CRLF);
	}

	inline std::string	CHANNELISFULL(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 471 " + chan.getName() + " :Cannot join channel (+l)" + CRLF);
	}

	inline std::string	UNKNOWNMODE(Client& target, Channel& chan, char c)
	{
		return (target.getPrefix() + " 472 " + c + " :is unknown mode char to me for " + chan.getName() + CRLF);
	}

	inline std::string	INVITEONLYCHAN(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 473 " + chan.getName() + " :Cannot join channel (+i)" + CRLF);
	}

	inline std::string	BADCHANNELKEY(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 475 " + chan.getName() + " :Cannot join channel (+k)" + CRLF);
	}

	inline std::string	CHANOPRIVSNEEDED(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 482 " + chan.getName() + " :You're not channel operator" + CRLF);
	}

	inline std::string	UMODEUNKNOWNFLAG(Client& target)
	{
		return (target.getPrefix() + " 501 :Unknown MODE flag" + CRLF);
	}
}

#endif
