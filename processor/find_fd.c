#include "minishell.h"

int		find_fdin(t_data *data)
{
	int fd;

	fd = 0;
	return (fd);
}

int		find_fdout(t_data *data)
{
	int fd;
	int ret;

	fd = 0;
	if (data->ar->type == '|')
	{
		ret = pipe(data->pipe_fd);
		if (ret == -1)
			ft_exit(10);
		fd = data->pipe_fd[1];
	}
	else
	{
		fd = data->orig_fd[1];
	}
	return (fd);
}