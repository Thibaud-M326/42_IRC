#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>

class Client
{
	private:
		std::string	_Prefix;
		std::string	_Username;
		std::string	_Nickname;
		std::string	_StrMode;
		std::string	_Ip_address;
		int			_Fd;

	public:
		/* class prerequisites */
		Client(const int fd, const char *ip_address);
		~Client();

		/* getters */
		std::string	getPrefix() const;
		std::string	getUsername() const;
		std::string	getNickname() const;
		std::string	get_StrMode() const;
		std::string	getIpAddress() const;
		int			getFd() const;

		/* setters */
		void	setPrefix();
		void	setUsername(std::string& Username);
		void	setNickname(std::string& Nickname);
		void	set_StrMode(std::string& StrMode);
		void	setIpAddress(std::string& Ip_address);
		void	setFd(int Fd);
};

#endif
