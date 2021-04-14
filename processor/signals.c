#include "minishell.h"

static void	signal_handler(int sig)
{
	int ret;

	ret = waitpid(-1, 0, WNOHANG);
	if (ret == -1)
	{
		display_error("minishell", NULL, strerror(errno));
		exit(-1);
	}
	if (ret)
		kill(1, sig);
}

void set_signals(t_data *data)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		ft_exit(-1, data, 1);
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
		ft_exit(-1, data, 1);
}