#ifndef IRC_HPP
# define IRC_HPP

namespace irc_macro
{
	const char CRLF[] = "\r\n";
	const char BOLD_GREEN[] = "\e[1;32m";
	const char BOLD_RED[] = "\e[1;31m";
	const char BOLD_BLUE[] = "\e[1;34m";
	const char BOLD_YELLOW[] = "\e[1;33m";
	const char BOLD_PURPLE[] = "\e[1;35m";
	const char BOLD_CYAN[] = "\e[1;36m";
	const char STOP_COLOR[] = "\e[0m";
}
using	irc_macro::CRLF;
using	irc_macro::BOLD_GREEN;
using	irc_macro::BOLD_RED;
using	irc_macro::BOLD_BLUE;
using	irc_macro::BOLD_YELLOW;
using	irc_macro::BOLD_PURPLE;
using	irc_macro::BOLD_CYAN;
using	irc_macro::STOP_COLOR;

#endif
