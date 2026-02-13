#include "Client.hpp"
#include <sstream>

Client::Client():
	_Prefix(""),
	_Username(""),
	_Nickname(""),
	_StrMode(""),
	_Ip_address(0),
	_Fd(0),
	_isRegistered(false),
	_Cbuffer("")
{
	std::cout << "Client constructor called" << std::endl;
}

Client::Client(const int fd, int ip_address):
	_Prefix(""),
	_Username(""),
	_Nickname(""),
	_StrMode(""),
	_Ip_address(ip_address),
	_Fd(fd),
	_isRegistered(false),
	_Cbuffer("")
{}

Client::~Client()
{
	std::cout << "Client destructor called" << std::endl;
}

std::string	Client::getPrefix() const
{
	return _Prefix;
}

std::string	Client::getUsername() const
{
	return _Username;
}

std::string	Client::getNickname() const
{
	return _Nickname;
}

std::string	Client::get_StrMode() const
{
	return _StrMode;
}

int	Client::getIpAddress() const
{
	return _Ip_address;
}

int	Client::getFd() const
{
	return _Fd;
}

std::string	Client::getBuffer() const
{
	return _Cbuffer;
}

bool	Client::getIsRegistered() const
{
	return _isRegistered;
}

void	Client::setPrefix()
{
	if (_Username != "" && _Nickname != "")
	{
		std::ostringstream	oss;
		oss << _Nickname << "!" << _Username << "@" << _Ip_address << " ";
		_Prefix = oss.str();
	}
}

void	Client::setUsername(std::string& Username)
{
	_Username = Username;
	setPrefix();
}

void	Client::setNickname(std::string& Nickname)
{
	_Nickname = Nickname;
	setPrefix();
}

void	Client::set_StrMode(std::string& StrMode)
{
	_StrMode = StrMode;
}

void	Client::setIpAddress(int& Ip_address)
{
	_Ip_address = Ip_address;
}

void	Client::setFd(int Fd)
{
	_Fd = Fd;
}

void	Client::setBuffer(std::string buffer)
{
	_Cbuffer = buffer;
}

void	Client::appendRawData(const char* readBuf)
{
	_Cbuffer.append(readBuf);
}

void	Client::setIsRegistered()
{
	_isRegistered = true; }
