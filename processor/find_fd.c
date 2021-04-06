#include "minishell.h"

int		find_fdin(t_data *data)
{
	int fd;

	fd = 0;
	if (data->pipe_fd[0])
	{
		fd = dup(data->pipe_fd[0]);
	}
	else
	{
		fd = dup(data->orig_fd[0]);
	}
	if (data->pipe_fd[0])
		close(data->pipe_fd[0]);
	data->pipe_fd[0] = 0;
	return (fd);
}

int		find_fdout(t_data *data, char type)
{
	int fd;
	int ret;

	fd = 0;
	if (type == '|')
	{
		ret = pipe(data->pipe_fd);
		if (ret == -1)
			ft_exit(10);
		fd = dup(data->pipe_fd[1]);
	}
	else
	{
		fd = dup(data->orig_fd[1]);
	}
	if (data->pipe_fd[1])
		close(data->pipe_fd[1]);
	data->pipe_fd[1] = 0;
	return (fd);
}