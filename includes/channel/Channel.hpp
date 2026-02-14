#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>

class Client;

class Channel
{
	private:
		std::string	_Name;
		std::string	_Topic;
		std::string	_Mode;
		std::string	_ModeParams;
		Client		*_Operator;

	public:
		/* class prerequisites */
		Channel();
		~Channel();

		/* getters */
		std::string	getName() const;
		std::string	getTopic() const;
		std::string	getMode() const;
		std::string	getModeParams() const;
		Client		*getOperator() const;

		/* setters */
		void	setName(std::string& Name);
		void	setTopic(std::string& Topic);
		void	setMode(std::string& Mode);
		void	setModeParams(std::string& ModeParams);
		void	setOperator(Client *Operator);
};

#endif
