#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <bitset>
# include <cstdlib>
# include <vector>
# include "Irc.hpp"

class Client;

class Channel
{
	private:
		std::string						_name;
		std::string						_topic;
		std::string						_key;
		std::bitset<ircMacro::NB_MODE>	_mode;
		std::vector<Client*>			_operators;
		std::vector<std::string>		_modeParams;
		std::vector<Client*>			_clientList;
		ssize_t							_limitNbUser;

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
		std::vector<Client*>			getOperators() const;
		std::vector<Client*>			getClientList() const;
		std::vector<int>				getClientsFd() const;
		std::vector<int>				getClientsFdButSource(int sourceFd) const;
		std::string						getKey() const;
		ssize_t							getLimitNbUser() const;
		std::string						getClientsStr() const;

		/* setters */
		void							setName(std::string& name);
		void							setTopic(std::string topic);
		void							setMode(t_modeEnum index, bool value);
		void							setModeParams(std::string& params, t_modeEnum index);
		void							setKey(std::string key);
		void							setLimitNbUser(ssize_t limit);

		void							addOperator(Client* ope);
		void							removeOperator(Client* ope);
		void							addClient(Client* client);
		void							removeClient(Client* client);
};

#endif
