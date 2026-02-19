#include "Client.hpp"
#include <sstream>
#include <iostream>

Client::Client():
	_prefix(""),
	_username(""),
	_nickname(""),
	_ip_address(0),
	_fd(0),
	_isRegistered(false),
	_cbuffer("")
{
	std::cout << "Client constructor called" << std::endl;
}

Client::Client(const int fd, int ip_address):
	_prefix(""),
	_username(""),
	_nickname(""),
	_ip_address(ip_address),
	_fd(fd),
	_isRegistered(false),
	_cbuffer("") {}

Client::~Client()
{
	std::cout << "Client destructor called" << std::endl;
}

std::string	Client::getPrefix() const
{
	return _prefix;
}

std::string	Client::getUsername() const
{
	return _username;
}

std::string	Client::getNickname() const
{
	return _nickname;
}

int	Client::getIpAddress() const
{
	return _ip_address;
}

int	Client::getFd() const
{
	return _fd;
}

std::string	Client::getBuffer() const
{
	return _cbuffer;
}

bool	Client::getIsRegistered() const
{
	return _isRegistered;
}

std::bitset<ircMacro::NB_MODE>	Client::getMode() const
{
	return _mode;
}

std::string	Client::getStrMode() const
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

std::string	Client::getModeParams() const
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

mapChannels	Client::getChannelList() const
{
	return _channelList;
}

void	Client::setPrefix()
{
	if (!_username.empty() && !_nickname.empty())
	{
		std::ostringstream	oss;
		oss << ":" << _nickname << "!" << _username << "@" << _ip_address << " ";
		_prefix = oss.str();
	}
}

void	Client::setUsername(std::string& username)
{
	_username = username;
	setPrefix();
}

void	Client::setNickname(std::string& nickname)
{
	_nickname = nickname;
	setPrefix();
}

void	Client::setIpAddress(int& ip_address)
{
	_ip_address = ip_address;
}

void	Client::setFd(int fd)
{
	_fd = fd;
}

void	Client::setBuffer(std::string buffer)
{
	_cbuffer = buffer;
}

void	Client::appendRawData(const char* readBuf)
{
	_cbuffer.append(readBuf);
}

void	Client::setIsRegistered()
{
	_isRegistered = true;
}

void	Client::setMode(t_modeEnum index, bool value)
{
	if (value)
		_mode.set(index);
	else
		_mode.reset(index);
}

void	Client::setModeParams(std::string& params, t_modeEnum index)
{
	_modeParams[index] = params;
}

void	Client::leaveChannel(Channel* channel)
{
	for (mapChannels::iterator it = _channelList.begin(); it != _channelList.end(); it++)
	{
		if (it->second == channel)
			_channelList.erase(it);
	}
}

void	Client::joinChannel(const std::string& chanName, Channel* Channel)
{
	_channelList.insert(std::make_pair(chanName, Channel));
}

void	Client::clearChannel()
{
	_channelList.clear();
}

bool 	Client::processClient()
{
	std::string clrf = "\r\n";
	std::size_t found;
	std::string rawCommands;
	std::string afterLastClrf;

	found = _cbuffer.rfind(clrf);
	if (found!=std::string::npos)
	{
		rawCommands = _cbuffer.substr(0, found);
		afterLastClrf = _cbuffer.substr(found + clrf.length());

		std::cout << "client fd " << _fd << " buffer\n||||\n" << _cbuffer << "|||| "<< std::endl;

		if (afterLastClrf.empty())
			return true;
	}
	return false;
}

void	Client::clearBuffer()
{
	_cbuffer.clear();
}

