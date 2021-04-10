#include "minishell.h"

static void	signal_handler(int sig)
{
	int ret;

	ret = waitpid(-1, 0, WNOHANG);
	if (ret)
		kill(1, sig);
}

void set_signals(t_data *data)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}