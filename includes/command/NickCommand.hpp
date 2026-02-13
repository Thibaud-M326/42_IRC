#ifndef NICKCOMMAND_HPP
# define NICKCOMMAND_HPP

# include "ACommand.hpp"

typedef enum e_NickEnum
{
	noNickNameGiven = 1,
	erroneusNickName = 2,
	nickNameInUse = 3,
	notRegistered = 4
}	t_NickEnum;

class NickCommand : public ACommand
{
	public:
		NickCommand(std::vector<std::string>& params);
		std::string	ExecuteCommand(Client& target, std::map<int, Client>& ClientArray, std::vector<Channel>& ChannelArray);

		void			setReplyArray(Client& target, std::string& badNickname);
		unsigned int	isValidNickname(std::map<int, Client>& ClientArray);
};

#endif
