#include <iostream>
#include <vector>
#include "Exception.hpp"
#include "Irc.hpp"
#include "Parse.hpp"
#include "Server.hpp"


std::string	getDate()
{
	std::ostringstream	oss;
	std::time_t now = std::time(NULL);
	std::tm* local = std::localtime(&now);

	oss << (local->tm_year + 1900) << "-"
		<< (local->tm_mon + 1) << "-"
		<< local->tm_mday;
	return oss.str().c_str();
}

namespace ircMacro
{
	std::string	DATE = getDate();
	std::string	PASSWORD;
	int			PORT = 6667;
}
//
// int main(int ac, char *av[])
// {
// 	if (ac == 2 && (!std::strcmp(av[1], "--help")
// 				|| !std::strcmp(av[1], "-h")))
// 	{
// 		ircDisplay::help();
// 		return 0;
// 	}
// 	if (ac != 3 || !verifArgs(av[1], av[2]))
// 	{
// 		ircDisplay::usage();
// 		return 1;
// 	}
// 	try
// 	{
// 		Server serv(ircMacro::PORT, ircMacro::PASSWORD);
//
// 		serv.init_server_socket();
// 		serv.init_epoll();
// 		ircDisplay::displayAsciiServ();
// 		serv.run();
// 	}
// 	catch (ExceptionPerror &e)
// 	{
// 		std::cerr << ircDisplay::BOLD_RED << e.what() << ircDisplay::STOP_COLOR << std::endl;
// 	}
// 	return 0;
// }


#include "Parse.hpp"
#include "ModeCommand.hpp"
#include "JoinCommand.hpp"

int	main(void)
{
	try
	{
		mapChannels	ChanArray;
		mapClients	Cliarray;
		Parse			parse("MODE #42 +k password");
		std::vector<std::vector<std::string> >	command = parse.parseCommand();
		ACommand*		cmd1 = new ModeCommand(command[0]);
		Client		client;
		Channel*	chan = new Channel();
		std::string	name = "#42";

		client.setIsRegistered();
		chan->setName(name);
		chan->addClient(&client);
		chan->addOperator(&client);
		client.joinChannel(name, chan);
		ChanArray.insert(std::make_pair("#42", chan));
		t_replyHandler	replyHandler;
		replyHandler = cmd1->ExecuteCommand(client, Cliarray, ChanArray);

		Client		client2;
		client2.setIsRegistered();
		std::string	name1("coucou");
		client2.setNickname(name1);
		Parse	parse1("JOIN #42");
		command = parse1.parseCommand();
		ACommand*		cmd2 = new JoinCommand(command[0]);

		t_replyHandler	replyHandler2 = cmd2->ExecuteCommand(client2, Cliarray, ChanArray);

		for (size_t i = 0; i < replyHandler.messages.size(); i++)
			std::cout << "CMD 1 : " << replyHandler.messages[i].reply << "\n";
		for (size_t i = 0; i < replyHandler2.messages.size(); i++)
			std::cout << "CMD 2 : " << replyHandler2.messages[i].reply << "\n";

		delete cmd1;
		delete cmd2;
		delete chan;
	}
	catch(...)
	{}
	return 0;
}

