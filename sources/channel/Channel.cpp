#include "Channel.hpp"
#include "Client.hpp"
#include <sstream>

Channel::Channel():
	_name(""),
	_topic(""),
	_key(""),
	_modeParams(5),
	_limitNbUser(-1) {}

Channel::~Channel() {}

std::string	Channel::getName() const
{
	return _name;
}

std::string	Channel::getTopic() const
{
	return _topic;
}

std::bitset<ircMacro::NB_MODE>	Channel::getMode() const
{
	return _mode;
}

std::string	Channel::getStrMode() const
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

std::vector<int>	Channel::getClientsFd() const
{
	std::vector<int>	clientsFd;

	for (size_t i = 0; i < _clientList.size(); i++)
	{
		clientsFd.push_back(_clientList[i]->getFd());
	}
	return clientsFd;
}

std::vector<int>	Channel::getClientsFdButSource(int sourceFd) const
{
	std::vector<int>	clientsFd;

	for (size_t i = 0; i < _clientList.size(); i++)
	{
		if (sourceFd != _clientList[i]->getFd())
			clientsFd.push_back(_clientList[i]->getFd());
	}
	return clientsFd;
}

std::vector<Client*>	Channel::getClientList() const
{
	return _clientList;
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

std::vector<Client*>	Channel::getOperators() const
{
	return _operators;
}

std::string	Channel::getKey() const
{
	return _key;
}

ssize_t	Channel::getLimitNbUser() const
{
	return _limitNbUser;
}

std::string	Channel::getClientsStr() const
{
	std::ostringstream	oss;

	for (size_t i = 0; i < _clientList.size(); i++)
	{
		for (size_t j = 0; j < _operators.size(); j++)
		{
			if (_clientList[i] == _operators[j])
				oss << "@";
		}
		oss << _clientList[i]->getNickname();

		if (i != _clientList.size() - 1)
			oss << " ";
	}
	return oss.str();
}

void	Channel::setName(std::string& name)
{
	_name = name;
}

void	Channel::setTopic(std::string topic)
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

void	Channel::addOperator(Client* ope)
{
	_operators.push_back(ope);
}

void	Channel::removeOperator(Client* ope)
{
	std::vector<Client*>::iterator it = _operators.begin();
	while (it != _operators.end())
	{
		if (*it == ope)
			break ;
		it++;
	}
	_operators.erase(it);
}

void	Channel::addClient(Client* client)
{
	_clientList.push_back(client);
}

void	Channel::removeClient(Client* client)
{
	for (std::vector<Client*>::iterator it = _clientList.begin(); it != _clientList.end(); it++)
	{
		if (*it == client)
			_clientList.erase(it);
	}
}

void	Channel::setKey(std::string key)
{
	_key = key;
}

void	Channel::setLimitNbUser(ssize_t limit)
{
	_limitNbUser = limit;
}

