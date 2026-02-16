#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Irc.hpp"
# include <bitset>
# include <vector>

class Channel;

class Client
{
	private:
		std::string						_prefix;
		std::string						_username;
		std::string						_nickname;
		int								_ip_address;
		int								_fd;
		bool							_isRegistered;
		std::bitset<ircMacro::NB_MODE>	_mode;
		std::vector<std::string>		_modeParams;
		mapChannels						_channelList;

		std::string						_cbuffer;

	public:
		/* class prerequisites */
		Client();
		Client(const int fd, const int ip_address);
		~Client();

		/* getters */
		bool							getIsRegistered() const;
		int								getIpAddress() const;
		int								getFd() const;
		std::string						getPrefix() const;
		std::string						getUsername() const;
		std::string						getNickname() const;
		std::string 					getBuffer() const;
		std::bitset<ircMacro::NB_MODE>	getMode() const;
		std::string						getStrMode() const;
		std::string 					getModeParams() const;

		/* setters */
		void		setPrefix();
		void		setUsername(std::string& Username);
		void		setNickname(std::string& Nickname);
		void		setIpAddress(int& Ip_address);
		void		setFd(int Fd);
		void		setBuffer(std::string buffer);
		void		setIsRegistered();
		void		setMode(t_modeEnum index, bool value);
		void		setModeParams(std::string& params, t_modeEnum index);
	
		void		appendRawData(const char* readBuffer);
		bool		processClient();
		void		clearBuffer();	
};

#endif
