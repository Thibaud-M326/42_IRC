#include <sys/types.h>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <sys/epoll.h>
#include <fcntl.h>

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
	const int	MAX_EVENTS = 10;
	const int	BUFFER_SIZE = 10;
	const char	SERVER[] = "Server: ";
	const char	CLIENT[] = "Client: ";
	const char	HELLO[] = "\e[1;33mHello from the server\e[0m\n";
}
using test::PORT;
using test::MAX_EVENTS;
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

void	exit_safe(int serv_socket, int client_sock,
		int epoll_fd, epoll_event *events, const char *msg)
{
	if (serv_socket > 0)
		close(serv_socket);
	if (client_sock > 0)
		close(client_sock);
	if (epoll_fd > 0)
		close(epoll_fd);
	if (events)
		free(events);
	
	if (msg)
		perror(msg);
	if (msg)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int set_nonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
        return -1;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int	main(void)
{
	std::cout << BOLD_BLUE << "The Server messages are in " << BOLD_YELLOW<<
		"Yellow" << BOLD_BLUE << " and the Client messages are in "
		<< BOLD_GREEN << "Green" << STOP_COLOR << '\n';
	int	serv_socket;
	int	client_socket;
	int	epoll_fd;
	int	nfds;
	epoll_event	*events, ev;
	sockaddr_in	addr {};
	socklen_t	addr_len {};

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_len = sizeof(addr);
	events = (epoll_event *)malloc(sizeof(epoll_event) * MAX_EVENTS);
	if (!events)
		exit(EXIT_FAILURE);

	memset(events, 0, sizeof(epoll_event) * MAX_EVENTS);

	serv_socket = socket(AF_INET, SOCK_STREAM, 0);

	set_nonblocking(serv_socket);

	if (serv_socket == -1)
		exit_safe(-1, -1, -1, events, "socket");
	
	int opt = 1;
	setsockopt(serv_socket,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	if (bind(serv_socket, (struct sockaddr *)&addr, addr_len) == -1)
		exit_safe(serv_socket, -1, -1, events, "bind");

	std::cout << BOLD_YELLOW << SERVER << "The socket server is set" << STOP_COLOR << '\n';

	if (listen(serv_socket, 1) == -1)
		exit_safe(serv_socket, -1, -1, events, "listen");

	ev.events = EPOLLIN;
	ev.data.fd = serv_socket;

	epoll_fd = epoll_create(1);
	if (epoll_fd == -1)
		exit_safe(serv_socket, -1, -1, events, "epoll_create");
	
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, serv_socket, &ev) == -1)
		exit_safe(serv_socket, -1, epoll_fd, events, "epoll_ctl");

	std::cout << BOLD_YELLOW << SERVER << "The socket server is in listening mode" << STOP_COLOR << '\n';

	for (;;)
	{
		nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
		if (nfds == -1)
			exit_safe(serv_socket, -1, epoll_fd, events, "epoll_wait");

		for (int i = 0; i < nfds; i++)
		{
			int	fd = events[i].data.fd;
			if (fd == serv_socket)
			{
				client_socket = accept(serv_socket, (struct sockaddr *)&addr, &addr_len);
				if (client_socket == -1)
				{
					if (errno == EAGAIN || errno == EWOULDBLOCK)
						break ;
					else
						exit_safe(serv_socket, -1, epoll_fd, events, "accept");
				}
				set_nonblocking(client_socket);
				ev.events = EPOLLIN;
				ev.data.fd = client_socket;

				if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket, &ev) == -1)
					exit_safe(serv_socket, client_socket, epoll_fd, events, "epoll_ctl");
			}
			else
			{
				std::map<int, std::string> client_buffers;
				char buf[BUFFER_SIZE];
				ssize_t bytes_read;

				while ((bytes_read = recv(fd, buf, BUFFER_SIZE, 0)) > 0)
				{
					client_buffers[fd].append(buf, bytes_read);

					size_t pos;
					while ((pos = client_buffers[fd].find("\n")) != std::string::npos)
					{
						std::string message = client_buffers[fd].substr(0, pos);
						client_buffers[fd].erase(0, pos + 1);

						std::cout << BOLD_BLUE << "Client: " << BOLD_GREEN << message << STOP_COLOR << '\n';

						if (send(fd, HELLO, ft_strlen(HELLO), 0) == -1)
							exit_safe(serv_socket, fd, epoll_fd, events, "send");

						if (message == "STOP")
						{
							client_buffers.~map();
							exit_safe(serv_socket, client_socket, epoll_fd, events, NULL);
						}
					}
				}

				if (bytes_read == 0 || (bytes_read < 0 && errno == ECONNRESET))
				{
					close(fd);
					epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
					client_buffers.erase(fd);
				}
				else if (bytes_read < 0 && errno != EAGAIN && errno != EWOULDBLOCK)
				{
					exit_safe(serv_socket, fd, epoll_fd, events, "recv");
				}
			}
		}
	}
	close(serv_socket);
	close(client_socket);
	free(events);
	return 0;
}

