#include "Client.hpp"

Client::Client():
	_prefix(""),
	_username(""),
	_nickname("*"),
	_ip_address(""),
	_fd(0),
	_isRegistered(false),
	_isConnected(false),
	_isNicknameSet(false),
	_cbuffer("") {}

Client::Client(const int fd, std::string ip_address):
	_prefix(""),
	_username(""),
	_nickname("*"),
	_ip_address(ip_address),
	_fd(fd),
	_isRegistered(false),
	_isConnected(false),
	_isNicknameSet(false),
	_cbuffer("") {}

Client::~Client()
{
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

std::string	Client::getIpAddress() const
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

mapChannels&	Client::getChannelList()
{
	return _channelList;
}

bool	Client::getIsConnected() const
{
	return _isConnected;
}

bool	Client::getISNicknameSet() const
{
	return _isNicknameSet;
}

void	Client::setIsConnected()
{
	_isConnected = true;
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
	if (nickname.empty())
		_nickname = "*";
	_nickname = nickname;
	_isNicknameSet = true;
	setPrefix();
}

void	Client::setIpAddress(std::string ip_address)
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

void	Client::leaveChannel(Channel* channel)
{
	for (mapChannels::iterator it = _channelList.begin(); it != _channelList.end(); )
	{
		if (it->second == channel)
		{
			mapChannels::iterator	tmp = it++;
			_channelList.erase(tmp);
		}
		else
			it++;
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

		ircDisplay::startRequest(_fd, rawCommands.size());

		if (afterLastClrf.empty())
			return true;
	}
	return false;
}

void	Client::clearBuffer()
{
	_cbuffer.clear();
}

