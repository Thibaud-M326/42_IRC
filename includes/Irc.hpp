#ifndef IRC_HPP
# define IRC_HPP

# include <ctime>
# include <iostream>
# include <map>
# include <sstream>

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
	const char			BOLD_GREEN[] = "\e[1;32m";
	const char			BOLD_RED[] = "\e[1;31m";
	const char			BOLD_BLUE[] = "\e[1;34m";
	const char			BOLD_YELLOW[] = "\e[1;33m";
	const char			BOLD_PURPLE[] = "\e[1;35m";
	const char			BOLD_CYAN[] = "\e[1;36m";
	const char			STOP_COLOR[] = "\e[0m";

	extern std::string	DATE;
	extern std::string	PASSWORD;
	extern int			PORT;

	inline void	displayAsciiServ()
	{
		std::cout << ircMacro::BOLD_GREEN << " ______ _______   _____ _____   _____ \n"
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

	const char			USAGE[] = "Usage: ircserv [PORT] [PASSWORD]\nTry 'ircserv --help' for more information.";

	inline const std::string help()
	{
		std::ostringstream	oss;

		oss << ircMacro::BOLD_BLUE << "Usage: ./ircserv [PORT] [PASSWORD]\n"
			<< "[PORT] = The port number on which the server will be"
			<< "listening for incoming IRC connections\n"
			<< "[PASSWORD] = The connection password. It will be needed"
			<< "by any IRC client that tries\nto connect to the server."
			<< "Only alpha numeric and '-', '_' characters are allowed (31 max)"
			<< ircMacro::STOP_COLOR;
		return oss.str();
	};

	const char			CRLF[] = "\r\n";
	const int			MAX_EVENT = 10;
	const char			NAME_SERVER[] = ":ircserv";
	const int			NB_CHAR_PASS_MAX = 32;
	const int			NB_CHAR_PASS_MIN = 4;
	const int			NB_MODE = 5;
	const int			NB_PORT_MAX = 65535;
	const int			READ_BUFFER_SIZE = 1024;
	const char			VERSION[] = "1.0";

	const char chanCharArray[] =
		{ '&', '#', '!', '+', '\0'};

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
}

#endif

