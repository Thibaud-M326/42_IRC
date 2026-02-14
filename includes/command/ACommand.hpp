#ifndef ACOMMAND_HPP
# define ACOMMAND_HPP

# include <vector>
# include <map>
# include <string>

class Client;
class Channel;

class ACommand
{
	protected:
		std::vector<std::string>	_CommandArray;

	public:
		ACommand(std::vector<std::string>& params);
		virtual std::string		ExecuteCommand(Client& target, std::map<int, Client*>& ClientArray, std::vector<Channel>& ChannelArray) = 0;
		bool					isSpecialChar(char c) const;
		virtual ~ACommand();
};

#endif
