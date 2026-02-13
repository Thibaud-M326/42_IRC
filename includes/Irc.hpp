#ifndef IRC_HPP
# define IRC_HPP

namespace ircMacro
{
	extern char	PASSWORD[];
	const char	CRLF[] = "\r\n";
	const bool	SUCCESS = 0;
	const char	specialCharArray[] =
		{ '[', '\\', ']', '^', '_',
			'`', '{', '|', '}', '\0' };
}

#endif
