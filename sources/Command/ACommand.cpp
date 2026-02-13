#include "ACommand.hpp"

namespace MacroCommand
{
	const int	SUCCESS = 0;
}

ACommand::ACommand(std::vector<std::vector<std::string> > params): _CommandArray(params) {}

ACommand::~ACommand() {}
