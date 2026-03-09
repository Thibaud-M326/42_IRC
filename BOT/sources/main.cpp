#include <iostream>
#include "FeurBot.hpp"

int main(int ac, char *av[])
{
	std::cout << REPLY;
	if (ac != 4)
	{
		std::cerr << "Usage: ./feurbot [HOST] [PORT] [PASSWORD]\n";
		return 1;
	}
	try
	{
		FeurBot feurbot(av[1], av[2], av[3]);

		feurbot.runFeurBot();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
