#include "Client.hpp"
#include <sstream>

Client::Client(const int fd, const char *ip_address):
	_Prefix(""),
	_Username(""),
	_Nickname(""),
	_StrMode(""),
	_Ip_address(ip_address),
	_Fd(fd) {}

Client::~Client() {}

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

std::string	Client::getIpAddress() const
{
	return _Ip_address;
}

int	Client::getFd() const
{
	return _Fd;
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

void	Client::setIpAddress(std::string& Ip_address)
{
	_Ip_address = Ip_address;
}

void	Client::setFd(int Fd)
{
	_Fd = Fd;
}

