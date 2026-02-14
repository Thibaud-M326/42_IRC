#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Irc.hpp"

class Channel;

class Client
{
	private:
		std::string	_Prefix;
		std::string	_Username;
		std::string	_Nickname;
		std::string	_StrMode;
		int			_Ip_address;
		int			_Fd;
		bool		_isRegistered;

		std::string	_Cbuffer;
		mapChannels	_channelList;

	public:
		/* class prerequisites */
		Client();
		Client(const int fd, const int ip_address);
		~Client();

		/* getters */
		bool		getIsRegistered() const;
		int			getIpAddress() const;
		int			getFd() const;
		std::string	getPrefix() const;
		std::string	getUsername() const;
		std::string	getNickname() const;
		std::string	get_StrMode() const;
		std::string getBuffer() const;

		/* setters */
		void		setPrefix();
		void		setUsername(std::string& Username);
		void		setNickname(std::string& Nickname);
		void		set_StrMode(std::string& StrMode);
		void		setIpAddress(int& Ip_address);
		void		setFd(int Fd);
		void		setBuffer(std::string buffer);
		void		setIsRegistered();
	
		void		appendRawData(const char* readBuffer);
};

#endif
