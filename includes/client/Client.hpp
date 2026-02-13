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
		int			_Ip_address;
		int			_Fd;

		std::string _Cbuffer;

	public:
		/* class prerequisites */
		Client();
		Client(const int fd, const int ip_address);
		~Client();

		/* getters */
		std::string	getPrefix() const;
		std::string	getUsername() const;
		std::string	getNickname() const;
		std::string	get_StrMode() const;
		int			getIpAddress() const;
		int			getFd() const;
		std::string getBuffer() const;

		/* setters */
		void	setPrefix();
		void	setUsername(std::string& Username);
		void	setNickname(std::string& Nickname);
		void	set_StrMode(std::string& StrMode);
		void	setIpAddress(int& Ip_address);
		void	setFd(int Fd);
		void	setBuffer(std::string buffer);

		void	appendRawData(const char* readBuffer);
};

#endif
