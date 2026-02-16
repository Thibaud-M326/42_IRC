#include "CommandFactory.hpp"
#include "InviteCommand.hpp"
#include "JoinCommand.hpp"
#include "KickCommand.hpp"
#include "ListCommand.hpp"
#include "ModeCommand.hpp"
#include "NickCommand.hpp"
#include "OperCommand.hpp"
#include "PassCommand.hpp"
#include "PrivMsgCommand.hpp"
#include "TopicCommand.hpp"
#include "UserCommand.hpp"

static ACommand*	createPrivMsg(std::vector<std::string>& commands)
{
	return new PrivMsgCommand(commands);
}

static ACommand*	createNick(std::vector<std::string>& commands)
{
	return new NickCommand(commands);
}

static ACommand*	createPass(std::vector<std::string>& commands)
{
	return new PassCommand(commands);
}

static ACommand*	createUser(std::vector<std::string>& commands)
{
	return new UserCommand(commands);
}

// static ACommand*	createInvite(std::vector<std::string>& commands)
// {
// 	return new InviteCommand(commands);
// }

// static ACommand*	createTopic(std::vector<std::string>& commands)
// {
// 	return new TopicCommand(commands);
// }

// static ACommand*	createMode(std::vector<std::string>& commands)
// {
// 	return new ModeCommand(commands);
// }

// static ACommand*	createKick(std::vector<std::string>& commands)
// {
// 	return new KickCommand(commands);
// }

// static ACommand*	createOper(std::vector<std::string>& commands)
// {
// 	return new OperCommand(commands);
// }

// static ACommand*	createList(std::vector<std::string>& commands)
// {
// 	return new ListCommand(commands);
// }

static ACommand*	createJoin(std::vector<std::string>& commands)
{
	return new JoinCommand(commands);
}

CommandFactory::CommandFactory()
{
	_registry["PRIVMSG"] = &createPrivMsg;
	_registry["NICK"] = &createNick;
	_registry["PASS"] = &createPass;
	_registry["USER"] = &createUser;
	// _registry["INVITE"] = &createInvite;
	// _registry["TOPIC"] = &createTopic;
	// _registry["MODE"] = &createMode;
	// _registry["KICK"] = &createKick;
	// _registry["OPER"] = &createOper;
	// _registry["LIST"] = &createList;
	_registry["JOIN"] = &createJoin;
}

ACommand*	CommandFactory::createCommand(std::vector<std::string>& params)
{
	std::map<std::string, CreateFunc>::iterator	it;

	it = _registry.find(params[0]);
	if (it != _registry.end())
	{
		return it->second(params);
	}
	return NULL;
}
