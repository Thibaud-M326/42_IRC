#ifndef COMMANDFACTORY_HPP
# define COMMANDFACTORY_HPP

# include <map>
# include "ACommand.hpp"

typedef ACommand* (*CreateFunc)(std::vector<std::string>&);

class CommandFactory
{
	private:
		std::map<std::string, CreateFunc> _registry;

	public:
		CommandFactory();
		ACommand* createCommand(std::vector<std::string>& params);
};

#endif
