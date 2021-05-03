#include "minishell.h"

static void	signal_handler(int sig)
{
	int	ret;

	(void)sig;
	ret = wait(&g_status);
	if (ret == -1)
	{
		display_error("minishell", NULL, strerror(errno));
		exit(-1);
	}
	if (ret)
	{
		g_status += 128;
		if (g_status == 130)
			ft_putstr_fd("\n", 1);
		if (g_status == 131)
			ft_putstr_fd("Quit: 3\n", 2);
	}
}

void	set_signals(t_data *data)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		ft_exit(-1, data, 1);
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
		ft_exit(-1, data, 1);
}
