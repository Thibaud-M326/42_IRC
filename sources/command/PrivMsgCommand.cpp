#include "PrivMsgCommand.hpp"

PrivMsgCommand::PrivMsgCommand(std::vector<std::string>& params): ACommand(params) {}

std::string	PrivMsgCommand::ExecuteCommand(Client& target, mapClients& ClientArray, mapChannels& ChannelArray) {
	(void)ClientArray;
	(void)ChannelArray;
	(void)target;
	return ("");
}
