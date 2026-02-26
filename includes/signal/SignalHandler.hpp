#ifndef SIGNALHANDLER_HPP
# define SIGNALHANDLER_HPP

# include <csignal>

class SignalHandler
{
	private:
		static volatile sig_atomic_t	_running;
		static void						handleSig(int signal);

	public:
		static void	initSignal();
		static bool	isRunning();
};

#endif
