#include "FeurBot.hpp"
#include <stdexcept>
#include <unistd.h>
#include <cstdlib>

FeurBot::FeurBot(std::string host, std::string port, std::string password)
{
	_password = password;
	_sock_addr.sin_family = AF_INET;
	_sock_addr.sin_port = htons(std::atoi(port.c_str()));
	_sock_addr.sin_addr.s_addr = inet_addr(host.c_str());
	if (_sock_addr.sin_addr.s_addr == INADDR_NONE)
		throw std::runtime_error("inet_addr() failed: invalid host");

	_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket_fd < 0)
		throw std::runtime_error("socket() failed");
}

FeurBot::~FeurBot()
{
	close(_socket_fd);
}
