#ifndef NICKCOMMAND_HPP
# define NICKCOMMAND_HPP

# include "ACommand.hpp"

typedef enum e_NickEnum
{
	noNickNameGiven = 1,
	erroneusNickName = 2,
	nickNameInUse = 3,
}	t_NickEnum;

class NickCommand : public ACommand
{
	private:
		const std::string	replyArray[4];
	public:
		NickCommand(std::vector<std::string>& params);
		std::string		ExecuteCommand(Client& target, std::map<int, Client>& ClientArray, std::vector<Channel>& ChannelArray);
};

#endif
