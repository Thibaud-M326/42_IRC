#include "Channel.hpp"
#include "Client.hpp"

Channel::Channel() {}

Channel::~Channel() {}

std::string	Channel::getName() const
{
	return _Name;
}

std::string	Channel::getTopic() const
{
	return _Topic;
}

std::string	Channel::getMode() const
{
	return _Mode;
}

std::string	Channel::getModeParams() const
{
	return _ModeParams;
}

Client	*Channel::getOperator() const
{
	return _Operator;
}

void	Channel::setName(std::string& Name)
{
	_Name = Name;
}

void	Channel::setTopic(std::string& Topic)
{
	_Topic = Topic;
}

void	Channel::setMode(std::string& Mode)
{
	_Mode = Mode;
}

void	Channel::setModeParams(std::string& ModeParams)
{
	_ModeParams = ModeParams;
}

void	Channel::setOperator(Client	*ope)
{
	_Operator = ope;
}

