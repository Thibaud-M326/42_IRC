#include <iostream>
#include "FeurBot.hpp"

int main(int ac, char *av[])
{
	if (ac != 4)
	{
		std::cerr << "Usage: ./feurbot [HOST] [PORT] [PASSWORD]\n";
		return 1;
	}
	try
	{
		FeurBot feurbot(av[1], av[2], av[3]);

		std::cout << "connectToServer" << std::endl;
		feurbot.connectToServer();
		std::cout << "getChannelList" << std::endl;
		feurbot.getChannelList();
		std::cout << "connectToChannels" << std::endl;
		feurbot.connectToChannels();
		std::cout << "SayFeur" << std::endl;
		feurbot.sayFeur();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
