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
	const char	HELLO[] = "\e[1;32mHello from the client\e[0m\r\n";
}
using test::PORT;
using test::SERVER;
using test::CLIENT;
using test::BUFFER_SIZE;
using test::HELLO;

int	ft_strlen(const char *s)
{
	int len = -1;
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
	int	sock;
	sockaddr_in	addr;
	char	buf[BUFFER_SIZE];

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);

	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		exit_safe(-1, -1, "socket");

	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		exit_safe(sock, -1, "connect");

	if (send(sock, HELLO, ft_strlen(HELLO), 0) == -1)
		exit_safe(sock, -1, "send");

	memset(buf, 0, BUFFER_SIZE);

	if (recv(sock, buf, BUFFER_SIZE - 1, 0) == -1)
		exit_safe(sock, -1, "recv");

	std::cout << buf << '\n';

	close(sock);

	return 0;
}
