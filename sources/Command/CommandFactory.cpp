#include "CommandFactory.hpp"
#include "PrivMsgCommand.hpp"
#include "NickCommand.hpp"
#include "InviteCommand.hpp"
#include "TopicCommand.hpp"
#include "ModeCommand.hpp"
#include "KickCommand.hpp"
#include "OperCommand.hpp"
#include "ListCommand.hpp"
#include "JoinCommand.hpp"
#include "CommandFactory.hpp"

static ACommand*	createPrivMsg(std::vector<std::vector<std::string> >& commands)
{
	return new PrivMsgCommand(commands);
}

static ACommand*	createNick(std::vector<std::vector<std::string> >& commands)
{
	return new NickCommand(commands);
}

static ACommand*	createInvite(std::vector<std::vector<std::string> >& commands)
{
	return new InviteCommand(commands);
}

static ACommand*	createTopic(std::vector<std::vector<std::string> >& commands)
{
	return new TopicCommand(commands);
}

static ACommand*	createMode(std::vector<std::vector<std::string> >& commands)
{
	return new ModeCommand(commands);
}

static ACommand*	createKick(std::vector<std::vector<std::string> >& commands)
{
	return new KickCommand(commands);
}

static ACommand*	createOper(std::vector<std::vector<std::string> >& commands)
{
	return new OperCommand(commands);
}

static ACommand*	createList(std::vector<std::vector<std::string> >& commands)
{
	return new ListCommand(commands);
}

static ACommand*	createJoin(std::vector<std::vector<std::string> >& commands)
{
	return new JoinCommand(commands);
}

CommandFactory::CommandFactory()
{
	_registry["PRIVMSG"] = &createPrivMsg;
	_registry["NICK"] = &createNick;
	_registry["INVITE"] = &createInvite;
	_registry["TOPIC"] = &createTopic;
	_registry["MODE"] = &createMode;
	_registry["KICK"] = &createKick;
	_registry["OPER"] = &createOper;
	_registry["LIST"] = &createList;
	_registry["JOIN"] = &createJoin;
}

ACommand*	CommandFactory::createCommand(std::vector<std::vector<std::string> >& params)
{
	std::map<std::string, CreateFunc>::iterator	it;

	it = _registry.find(params[0][0]);
	if (it != _registry.end())
	{
		return it->second(params);
	}
	return NULL;
}
