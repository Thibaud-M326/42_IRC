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

	extern std::string	DATE;
	extern std::string	PASSWORD;
	extern int			PORT;

	const char			CRLF[] = "\r\n";
	const int			MAX_EVENT = 10;
	const int			MAX_BYTES = 512;
	const char			NAME_SERVER[] = ":ircserv";
	const int			NB_CHAR_PASS_MAX = 32;
	const int			NB_CHAR_PASS_MIN = 4;
	const int			NB_MODE = 5;
	const int			NB_PORT_MAX = 65535;
	const int			READ_BUFFER_SIZE = 1024;
	const char			VERSION[] = "1.0";

	const char			chanCharArray[] =
							{ '&', '#', '!', '+', '\0'};

	const char			modeCharArray[] =
							{ 'l', 'o', 'k', 't', 'i', '\0' };

	inline std::string	getDate()
	{
		std::ostringstream	oss;
		std::time_t now = std::time(NULL);
		std::tm* local = std::localtime(&now);

		oss << (local->tm_year + 1900) << "-"
			<< (local->tm_mon + 1) << "-"
			<< local->tm_mday;
		return oss.str().c_str();
	}

	typedef enum e_modeChar
	{
		modeUserLimit = 'l',
		modeOperatorPrivileges = 'o',
		modeRestrictPassword = 'k',
		modeRestrictTopic = 't',
		modeInviteOnly = 'i',
		modeFailure = '\0'
	} t_modeChar;

	const char			specialCharArray[] =
							{ '[', '\\', ']', '^', '_',
								'`', '{', '|', '}', '\0' };
}

namespace ircDisplay
{
	const char			BOLD_GREEN[] = "\e[1;32m";
	const char			BOLD_RED[] = "\e[1;31m";
	const char			BOLD_BLUE[] = "\e[1;34m";
	const char			BOLD_YELLOW[] = "\e[1;33m";
	const char			BOLD_PURPLE[] = "\e[1;35m";
	const char			BOLD_CYAN[] = "\e[1;36m";
	const char			STOP_COLOR[] = "\e[0m";

	inline void	usage()
	{
		std::cerr << ircDisplay::BOLD_RED
			<< "Usage: ircserv [PORT] [PASSWORD]\nTry 'ircserv --help' for more information."
			<< ircDisplay::STOP_COLOR << std::endl;
	}

	inline void	displayAsciiServ()
	{
		std::cout << ircDisplay::BOLD_GREEN << " ______ _______   _____ _____   _____ \n"
			<< "|  ____|__   __| |_   _|  __ \\ / ____|\n"
			<< "| |__     | |      | | | |__) | |\n"
			<< "|  __|    | |      | | |  _  /| |\n"
			<< "| |       | |     _| |_| | \\ \\| |____\n"
			<< "|_|       |_|    |_____|_|  \\_\\\\_____|\n\n" << ircDisplay::BOLD_BLUE
			<< "======================================\n" << ircDisplay::BOLD_YELLOW
			<< "	FT_IRC - 42 Network\n" << ircDisplay::BOLD_BLUE
			<< "======================================\n"
			<< "Listening on : " << ircDisplay::BOLD_YELLOW << ircMacro::PORT
			<< ircDisplay::BOLD_BLUE << "\nStatus       : " << ircDisplay::BOLD_YELLOW << "ONLINE\n"
			<< ircDisplay::BOLD_BLUE << "\nProtocol     : " << ircDisplay::BOLD_YELLOW << "IRC"
			<< ircDisplay::STOP_COLOR << std::endl;
	}

	inline void	help()
	{
		std::cout << ircDisplay::BOLD_BLUE << "Usage: ./ircserv PORT PASSWORD\n"
			<< "PORT: The port number on which the server will be"
			<< "listening for incoming IRC connections. It must be between 1024 and 65345\n"
			<< "PASSWORD: The connection password. It will be needed"
			<< "by any IRC client that tries\nto connect to the server."
			<< "Only alpha numeric and '-', '_' characters are allowed (31 max)"
			<< ircDisplay::STOP_COLOR << std::endl;
	};

	inline void	send(int fd, size_t replyLength, std::string reply)
	{
		std::cout << ircDisplay::BOLD_BLUE << "[" << ircDisplay::BOLD_CYAN
			<< "SEND" << ircDisplay::BOLD_BLUE << "] fd: " << ircDisplay::BOLD_YELLOW
			<< fd << ircDisplay::BOLD_BLUE << " | " << ircDisplay::BOLD_YELLOW
			<< replyLength << ircDisplay::BOLD_BLUE << " bytes\n"
			 << ircDisplay::BOLD_YELLOW << reply << ircDisplay::STOP_COLOR << std::endl;
	}

	inline void	readClientDisco(int fd)
	{
		std::cout << ircDisplay::BOLD_RED << "[" << ircDisplay::BOLD_CYAN
			<< "READ" << ircDisplay::BOLD_RED << "] Client Disconnected (fd: "
			<< ircDisplay::BOLD_YELLOW << fd << ircDisplay::BOLD_RED << ")"
			<< ircDisplay::STOP_COLOR << std::endl;
	}

	inline void	accept(int fd)
	{
		std::cout << ircDisplay::BOLD_BLUE << "[" << ircDisplay::BOLD_CYAN
			<< "ACCEPT" << ircDisplay::BOLD_BLUE << "] Client Connected (fd: "
			<< ircDisplay::BOLD_YELLOW << fd << ircDisplay::BOLD_BLUE << ")"
			<< ircDisplay::STOP_COLOR << std::endl;
	}

	inline void	epollInit(int fd)
	{
		std::cout << ircDisplay::BOLD_BLUE << "[" << ircDisplay::BOLD_CYAN
			<< "EPOLL" << ircDisplay::BOLD_BLUE << "] Epoll initialized (fd: "
			<< ircDisplay::BOLD_YELLOW << fd << ircDisplay::BOLD_BLUE << ")"
			<< ircDisplay::STOP_COLOR << std::endl;
	}

	inline void	initServ()
	{
		std::cout << ircDisplay::BOLD_BLUE << "[" << ircDisplay::BOLD_CYAN
			<< "INIT" << ircDisplay::BOLD_BLUE
			<< "] Server socket created and listening on port "
			<< ircDisplay::BOLD_YELLOW << ircMacro::PORT
			<< ircDisplay::STOP_COLOR << std::endl;
	}

	inline void	startRequest(int fd, size_t commandLentgh)
	{
		std::cout << ircDisplay::BOLD_GREEN
			<< "\n================ START REQUEST ================\n"
			<< ircDisplay::BOLD_BLUE << "[" << ircDisplay::BOLD_CYAN
			<< "PARSE" << ircDisplay::BOLD_BLUE
			<< "] Client fd: "
			<< ircDisplay::BOLD_YELLOW << fd << ircDisplay::BOLD_BLUE
			<< " | Buffer: " << ircDisplay::BOLD_YELLOW << commandLentgh
			<< ircDisplay::BOLD_BLUE << " bytes"
			<< ircDisplay::STOP_COLOR << std::endl;
	}

	inline void endRequest()
	{
		std::cout << ircDisplay::BOLD_RED
			<< "================ END REQUEST ================"
			<< ircDisplay::STOP_COLOR << std::endl;
	}

	inline void	msgTarget(std::string target)
	{
		std::cout << ircDisplay::BOLD_BLUE << "Message Target : "
			<< ircDisplay::BOLD_YELLOW << target << ircDisplay::STOP_COLOR
			<< std::endl;
	}
}

#endif

