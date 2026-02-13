#include "ACommand.hpp"
#include "Irc.hpp"
ACommand::ACommand(std::vector<std::string>& params, std::string& password): _CommandArray(params), _password(password) {}

ACommand::~ACommand() {}

bool	ACommand::isSpecialChar(char c) const
{
	for (size_t i = 0; ircMacro::specialCharArray[i]; i++)
	{
		if (c == ircMacro::specialCharArray[i])
			return true;
	}
	return false;
}
