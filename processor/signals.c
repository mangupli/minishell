#include "minishell.h"

static void	signal_handler(int sig)
{
	int status;
	if (sig == SIGINT)
	{
		status = waitpid(-1, 0, 0);
		printf("\nstatus %d\n", status);
	}
}


void set_signals(t_data *data)
{
	signal(SIGINT, signal_handler);

}