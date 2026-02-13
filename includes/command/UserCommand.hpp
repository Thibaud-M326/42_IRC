#ifndef USERCOMMAND_HPP
# define USERCOMMAND_HPP

# include "ACommand.hpp"

typedef enum e_UserEnum
{
	needMoreParams = 1,
	alreadyRegistred = 2,
}	t_UserEnum;

class UserCommand : public ACommand
{
	public:
		UserCommand(std::vector<std::string>& params);
		std::string		ExecuteCommand(Client& target, std::map<int, Client>& ClientArray, std::vector<Channel>& ChannelArray);
		void			setReplyArray(Client& target, std::string realName, int index);
		bool			isValidParams();
};

#endif
