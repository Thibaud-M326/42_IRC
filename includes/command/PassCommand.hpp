#ifndef PASSCOMMAND_HPP
# define PASSCOMMAND_HPP

# include "ACommand.hpp"

typedef enum e_PassEnum
{
	passNeedMoreParams = 0,
	passAlreadyRegistred = 1,
	passPasswdMissmatch = 2

}	t_PassEnum;

class PassCommand : public ACommand
{
	public:
		PassCommand(std::vector<std::string>& params);
		std::string		ExecuteCommand(Client& target, std::map<int, Client>& ClientArray, std::vector<Channel>& ChannelArray);
		void			setReplyArray(Client& target);
};

#endif
