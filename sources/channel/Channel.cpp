#include "Channel.hpp"
#include <sstream>

Channel::Channel() {}

Channel::~Channel() {}

std::string	Channel::getName() const
{
	return _name;
}

std::string	Channel::getTopic() const
{
	return _topic;
}

std::string	Channel::getMode() const
{
	if (!_mode.count())
		return "";

	std::ostringstream	oss;

	oss << '+';
	for (size_t i = _mode.size() -1; i > 0; i--)
	{
		if (_mode[i])
			oss << ircMacro::modeCharArray[i];
	}
	return oss.str();
}

std::string	Channel::getModeParams() const
{
	std::ostringstream	oss;
	for (size_t i = 0; i < _modeParams.size(); i++)
	{
		oss << _modeParams[i];
		if (!_modeParams[i].empty() && i != _modeParams.size() - 1)
			oss << ' ';
	}
	return oss.str();
}

Client	*Channel::getOperator() const
{
	return _operator;
}

void	Channel::setName(std::string& name)
{
	_name = name;
}

void	Channel::setTopic(std::string& topic)
{
	_topic = topic;
}

void	Channel::setMode(t_modeEnum index, bool value)
{
	if (value)
		_mode.set(index);
	else
		_mode.reset(index);
}

void	Channel::setModeParams(std::string& params, t_modeEnum index)
{
	_modeParams[index] = params;
}

void	Channel::setOperator(Client	*ope)
{
	_operator = ope;
}

