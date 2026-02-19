#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <bitset>
# include <vector>
# include "Irc.hpp"

class Client;

class Channel
{
	private:
		std::string						_name;
		std::string						_topic;
		std::bitset<ircMacro::NB_MODE>	_mode;
		Client*							_operator;
		std::vector<std::string>		_modeParams;
		std::vector<Client*>			_clientList;
		std::string						_key;

	public:
		/* class prerequisites */
		Channel();
		~Channel();

		/* getters */
		std::string						getName() const;
		std::string						getTopic() const;
		std::string						getStrMode() const;
		std::bitset<ircMacro::NB_MODE>	getMode() const;
		std::string						getModeParams() const;
		Client	   						*getOperator() const;
		std::vector<Client*>			getClientList() const;
		std::vector<int>				getClientsFd() const;
		std::vector<int>				getClientsFdButSource(int sourceFd) const;
		std::string						getKey() const;

		/* setters */
		void							setName(std::string& name);
		void							setTopic(std::string& topic);
		void							setMode(t_modeEnum index, bool value);
		void							setModeParams(std::string& params, t_modeEnum index);
		void							setOperator(Client *ope);
		void							setKey(std::string& key);

		void							addClient(Client* client);
		void							removeClient(Client* client);
};

#endif
