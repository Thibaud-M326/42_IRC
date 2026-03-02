#ifndef IRC_HPP
# define IRC_HPP

# include <map>
# include <string>
# include <iostream>

class Client;
class Channel;

typedef enum e_modeEnum
{
	userLimit = 0, // 'l'
	operatorPrivileges = 1, // 'o'
	restrictPassword = 2, // 'k'
	restrictTopic = 3, // 't'
	inviteOnly = 4, // 'i'
	failure = 5
}	t_modeEnum;

typedef	std::map<int, Client*>			mapClients;
typedef	std::map<std::string, Channel*>	mapChannels;

namespace ircMacro
{
	const char			NAME_SERVER[] = ":ircserv";
	const char			VERSION[] = "1.0";
	const char			CRLF[] = "\r\n";
	const char	PORT[] = "6667";
	const char			BOLD_GREEN[] = "\e[1;32m";
	const char			BOLD_RED[] = "\e[1;31m";
	const char			BOLD_BLUE[] = "\e[1;34m";
	const char			BOLD_YELLOW[] = "\e[1;33m";
	const char			BOLD_PURPLE[] = "\e[1;35m";
	const char			BOLD_CYAN[] = "\e[1;36m";
	const char			STOP_COLOR[] = "\e[0m";
	const char	PASSWORD[] = "password";
	const bool			SUCCESS = 0;
	const int			NB_MODE = 5;
	const char			INVALID[] = "Invalid";

	const char	modeCharArray[] =
		{ 'l', 'o', 'k', 't', 'i', '\0' };

	typedef enum e_modeChar
	{
		modeUserLimit = 'l',
		modeOperatorPrivileges = 'o',
		modeRestrictPassword = 'k',
		modeRestrictTopic = 't',
		modeInviteOnly = 'i',
		modeFailure = '\0'
	} t_modeChar;

	const char	specialCharArray[] =
		{ '[', '\\', ']', '^', '_',
			'`', '{', '|', '}', '\0' };
	const char chanCharArray[] =
		{ '&', '#', '!', '+', '\0'};

	inline void	displayAsciiServ(void)
	{
		std::cout << ircMacro::BOLD_GREEN << "______ _______   _____ _____   _____ \n"
			<< "|  ____|__   __| |_   _|  __ \\ / ____|\n"
			<< "| |__     | |      | | | |__) | |\n"
			<< "|  __|    | |      | | |  _  /| |\n"
			<< "| |       | |     _| |_| | \\ \\| |____\n"
			<< "|_|       |_|    |_____|_|  \\_\\\\_____|\n\n" << ircMacro::BOLD_BLUE
			<< "======================================\n" << ircMacro::BOLD_YELLOW
			<< "	FT_IRC - 42 Network\n" << ircMacro::BOLD_BLUE
			<< "======================================\n"
			<< "Listening on : " << ircMacro::BOLD_YELLOW << ircMacro::PORT
			<< ircMacro::BOLD_BLUE << "\nStatus       : " << ircMacro::BOLD_YELLOW << "ONLINE\n"
			<< ircMacro::BOLD_BLUE << "\nProtocol     : " << ircMacro::BOLD_YELLOW << "IRC" << std::endl;
	}
}

#endif
