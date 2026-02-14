#ifndef IRC_HPP
# define IRC_HPP

namespace ircMacro
{
	const char CRLF[] = "\r\n";
	const char BOLD_GREEN[] = "\e[1;32m";
	const char BOLD_RED[] = "\e[1;31m";
	const char BOLD_BLUE[] = "\e[1;34m";
	const char BOLD_YELLOW[] = "\e[1;33m";
	const char BOLD_PURPLE[] = "\e[1;35m";
	const char BOLD_CYAN[] = "\e[1;36m";
	const char STOP_COLOR[] = "\e[0m";
	const char	PASSWORD[] = "password";
	const bool	SUCCESS = 0;
	const char	specialCharArray[] =
		{ '[', '\\', ']', '^', '_',
			'`', '{', '|', '}', '\0' };
}

#endif
