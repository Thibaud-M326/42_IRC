#include "PrivMsgCommand.hpp"

PrivMsgCommand::PrivMsgCommand(std::vector<std::string>& params): ACommand(params) {}

std::string	PrivMsgCommand::ExecuteCommand(Client& target, std::map<int, Client*>& ClientArray, std::vector<Channel>& ChannelArray) {
	(void)ClientArray;
	(void)ChannelArray;
	return ("");
}
