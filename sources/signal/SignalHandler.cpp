#include "SignalHandler.hpp"
#include <unistd.h>

volatile sig_atomic_t	SignalHandler::_running = 1;

void	SignalHandler::handleSig(int signal)
{
	if (signal == SIGINT || signal == SIGTERM)
		_running = 0;
}

void	SignalHandler::initSignal()
{
	struct sigaction	sa;

	sa.sa_handler = SignalHandler::handleSig;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	signal(SIGPIPE, SIG_IGN);
}

bool	SignalHandler::isRunning()
{
	return static_cast<bool>(_running);
}

