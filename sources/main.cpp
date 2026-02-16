#include "Server.hpp"
#include <iostream>
#include "Irc.hpp"

int main()
{
	try 
	{
		Server serv("6667", ircMacro::PASSWORD);

		serv.init_server_socket();
		serv.init_epoll();
		serv.run();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}
//
// #include "Parse.hpp"
// #include "CommandFactory.hpp"
//
// int	main(void)
// {
// 	Parse parse("JOIN #chan1,#chan2 pass1,pass2");
// 	std::vector<std::vector<std::string> > commands;
// 	CommandFactory factory;
//
//
// 	commands = parse.parseCommand();
// 	parse.display_vec(commands);
// 	ACommand*	cmd = factory.createCommand(commands[0]);
// 	Client	cli;
// 	mapChannels chan;
// 	mapClients client;
// 	cmd->ExecuteCommand(cli, client, chan);
// 	delete cmd;
// }
