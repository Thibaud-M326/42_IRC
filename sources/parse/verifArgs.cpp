#include "Irc.hpp"
#include <cstdlib>
#include <vector>

bool	verifArgs(std::string port, std::string password)
{
	std::stringstream	ssPort(port);
	int		tmpPort;
	
	ssPort >> tmpPort;

	if (!ssPort.eof())
		return false;

	if (tmpPort > ircMacro::NB_PORT_MAX
			|| tmpPort < 0
			|| password.size() > ircMacro::NB_CHAR_PASS_MAX
			|| password.size() < ircMacro::NB_CHAR_PASS_MIN)
		return false;

	for (size_t i = 0; password[i]; i++)
	{
		if (!std::isalnum(password[i])
				&& password[i] != '-'
				&& password[i] != '_')
		{
			return false;
		}
	}

	ircMacro::PASSWORD = password;
	ircMacro::PORT = tmpPort;

	return true;
}

