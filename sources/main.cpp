#include "Server.hpp"

int main()
{
	Server serv("6667", "password");

	serv.init_server_socket();
	serv.init_epoll();
	serv.run();
}