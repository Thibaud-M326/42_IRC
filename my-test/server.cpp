#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <cstring>

namespace Color
{
        const char BOLD_BLUE[] = "\e[1;34m";
        const char BOLD_CYAN[] = "\e[1;36m";
        const char BOLD_GREEN[] = "\e[1;32m";
        const char BOLD_RED[] = "\e[1;31m";
        const char BOLD_PURPLE[] = "\e[1;35m";
        const char BOLD_YELLOW[] = "\e[1;33m";
        const char STOP_COLOR[] = "\e[0m";
}

using Color::BOLD_BLUE;
using Color::BOLD_CYAN;
using Color::BOLD_GREEN;
using Color::BOLD_RED;
using Color::BOLD_PURPLE;
using Color::BOLD_YELLOW;
using Color::STOP_COLOR;

namespace test
{
	const int	PORT = 6697;
	const int	BUFFER_SIZE = 1024;
	const char	SERVER[] = "Server: ";
	const char	CLIENT[] = "Client: ";
	const char	HELLO[] = "\e[1;33mHello from the server\e[0m";
}
using test::PORT;
using test::SERVER;
using test::CLIENT;
using test::BUFFER_SIZE;
using test::HELLO;

int	ft_strlen(const char *s)
{
	int	len = -1;
	while (s[++len])
		;
	return len;
}

void	exit_safe(int server_sock, int client_sock, const char *msg)
{
	if (server_sock > 0)
		close(server_sock);
	if (client_sock > 0)
		close(client_sock);
	perror(msg);
	exit(EXIT_FAILURE);
}

int	main(void)
{
	std::cout << BOLD_BLUE << "The Server messages are in " << BOLD_YELLOW<<
		"Yellow" << BOLD_BLUE << " and the Client messages are in "
		<< BOLD_GREEN << "Green" << STOP_COLOR << '\n';
	int	server_sock;
	int	client_socket;
	sockaddr_in	addr {};
	socklen_t	addr_len {};
	char	buf[BUFFER_SIZE];

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_len = sizeof(addr);

	server_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (server_sock == -1)
		exit_safe(-1, -1, "socket");
	
	int opt = 1;
	setsockopt(server_sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	if (bind(server_sock, (struct sockaddr *)&addr, addr_len) == -1)
		exit_safe(server_sock, -1, "bind");

	std::cout << BOLD_YELLOW << SERVER << "The socket server is set" << STOP_COLOR << '\n';

	if (listen(server_sock, 1) == -1)
		exit_safe(server_sock, -1, "listen");

	std::cout << BOLD_YELLOW << SERVER << "The socket server is in listening mode" << STOP_COLOR << '\n';

	for (int i = 0; i < 3; i++)
	{
		memset(buf, 0, BUFFER_SIZE);

		client_socket = accept(server_sock, (struct sockaddr *)&addr, &addr_len);
		if (client_socket == -1)
			exit_safe(server_sock, -1, "accept");

		if (recv(client_socket, buf, BUFFER_SIZE, 0) == -1)
			exit_safe(server_sock, client_socket, "recv");

		std::cout << BOLD_BLUE << CLIENT << buf  << STOP_COLOR << '\n';

		if (send(client_socket, HELLO, ft_strlen(HELLO), 0) == -1)
			exit_safe(server_sock, client_socket, "send");
	}
	close(server_sock);
	close(client_socket);

	return 0;
}
