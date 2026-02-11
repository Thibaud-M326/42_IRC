#include "Channel.hpp"
#include "Client.hpp"

namespace irc_macro
{
	const char CRLF[] = "\r\n";
}
using	irc_macro::CRLF;

namespace error_code
{
	inline std::string	ERR_NOSUCHNICK(Client& target)
	{
		return (target.getPrefix() + " 401 " + target.getNickname() + " :No such nick/chan" + CRLF);
	}

	inline std::string	ERR_NOSUCHCHANNEL(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 403 " + chan.getName() + " :No such channel" + CRLF);
	}

	inline std::string	ERR_TOOMANYCHANNELS(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 405 " + chan.getName() + " :You have joined too many channels" + CRLF);
	}

	inline std::string	ERR_NORECIPIENT(Client& target, std::string command)
	{
		return (target.getPrefix() + " 411 :No recipient given (" + command + ")" + CRLF);
	}

	inline std::string	ERR_NOTEXTTOSEND(Client& target)
	{
		return (target.getPrefix() + " 412 :No text to send" + CRLF);
	}

	inline std::string	ERR_UNKNOWNCOMMAND(Client& target, std::string command)
	{
		return (target.getPrefix() + " 421 " + command + " :Unknown command" + CRLF);
	}

	inline std::string	ERR_NEEDMOREPARAMS(Client& target, std::string command)
	{
		return (target.getPrefix() + " 461 " + command + " :Not enough parameters" + CRLF);
	}

	inline std::string	ERR_ALREADYREGISTERED(Client& target)
	{
		return (target.getPrefix() + " 462 :Unauthorized command (already registered)" + CRLF);
	}

	inline std::string	ERR_PASSWDMISMATCH(Client& target)
	{
		return (target.getPrefix() + " 464 :Password incorrect" + CRLF);
	}

	inline std::string	ERR_NONICKNAMEGIVEN(Client& target)
	{
		return (target.getPrefix() + " 431 :No nickname given" + CRLF);
	}

	inline std::string	ERR_ERRONEUSNICKNAME(Client& target, std::string nickname)
	{
		return (target.getPrefix() + " 432 " + nickname + " :Erroneous nickname" + CRLF);
	}

	inline std::string	ERR_NICKNAMEINUSE(Client& target, std::string nickname)
	{
		return (target.getPrefix() + " 433 " + nickname + " :Nickaname is already in use" + CRLF);
	}

	inline std::string	ERR_USERNOTINCHANNEL(Client& target, Channel& chan, std::string nick_list)
	{
		return (target.getPrefix() + " 441 " + nick_list + " " + chan.getName() + " :They aren't on that channel" + CRLF);
	}

	inline std::string	ERR_NOTONCHANNEL(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 442 " + chan.getName() + " :You're not on that channel" + CRLF);
	}

	inline std::string	ERR_USERONCHANNEL(Client& target, Channel& chan, std::string user)
	{
		return (target.getPrefix() + " 443 " + user + chan.getName() + " :Is already on channel" + CRLF);
	}

	inline std::string	ERR_KEYSET(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 467 " + chan.getName() + " :Channel key already set" + CRLF);
	}

	inline std::string	ERR_CHANNELISFULL(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 471 " + chan.getName() + " :Cannot join channel (+l)" + CRLF);
	}

	inline std::string	ERR_UNKNOWNMODE(Client& target, Channel& chan, char c)
	{
		return (target.getPrefix() + " 472 " + c + " :is unknown mode char to me for " + chan.getName() + CRLF);
	}

	inline std::string	ERR_INVITEONLYCHAN(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 473 " + chan.getName() + " :Cannot join channel (+i)" + CRLF);
	}

	inline std::string	ERR_BADCHANNELKEY(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 475 " + chan.getName() + " :Cannot join channel (+k)" + CRLF);
	}

	inline std::string	ERR_CHANOPRIVSNEEDED(Client& target, Channel& chan)
	{
		return (target.getPrefix() + " 482 " + chan.getName() + " :You're not channel operator" + CRLF);
	}

	inline std::string	ERR_UMODEUNKNOWNFLAG(Client& target)
	{
		return (target.getPrefix() + " 501 :Unknown MODE flag" + CRLF);
	}
}

