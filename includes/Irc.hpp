#ifndef IRC_HPP
# define IRC_HPP

# include <map>
# include <string>

class Client;
class Channel;

typedef enum e_modeEnum
{
	inviteOnly = 0,
	restrictTopic = 1,
	restrictPassword = 2,
	operatorPrivileges = 4,
	userLimit = 5
}	t_modeEnum;

typedef	std::map<int, Client*>			mapClients;
typedef	std::map<std::string, Channel*>	mapChannels;

namespace ircMacro
{
	const char	CRLF[] = "\r\n";
	const char	BOLD_GREEN[] = "\e[1;32m";
	const char	BOLD_RED[] = "\e[1;31m";
	const char	BOLD_BLUE[] = "\e[1;34m";
	const char	BOLD_YELLOW[] = "\e[1;33m";
	const char	BOLD_PURPLE[] = "\e[1;35m";
	const char	BOLD_CYAN[] = "\e[1;36m";
	const char	STOP_COLOR[] = "\e[0m";
	const char	PASSWORD[] = "password";
	const bool	SUCCESS = 0;
	const int	NB_MODE = 5;

	const char	modeCharArray[] =
		{ 'l', 'o', 'k', 't', 'i' };

	const char	specialCharArray[] =
		{ '[', '\\', ']', '^', '_',
			'`', '{', '|', '}', '\0' };
}

#endif
