#include "minishell.h"

int		find_fdin(t_data *data)
{
	printf("***\nlooking for fd_in\n\n");


	int fd;

	fd = 0;
	if (data->pipe_fd[0])
	{
		printf("found pipe[0]\n");
		fd = dup(data->pipe_fd[0]);
	}
	else
	{
		printf("not found pipe[0]\n");
		fd = dup(data->orig_fd[0]);
	}
	if (data->pipe_fd[0])
		close(data->pipe_fd[0]);
	data->pipe_fd[0] = 0;
	return (fd);
}

int		find_fdout(t_data *data)
{
	printf("***\nlooking for fd_out\n\n");
	int fd;
	int ret;

	fd = 0;
	if (data->ar->type == '|')
	{
		ret = pipe(data->pipe_fd);
		printf("made pipe, took an output\n");
		if (ret == -1)
			ft_exit(10);
		fd = dup(data->pipe_fd[1]);
	}
	else
	{
		printf("no type, go to original output\n");
		fd = dup(data->orig_fd[1]);
	}
	if (data->pipe_fd[1])
		close(data->pipe_fd[1]);
	data->pipe_fd[1] = 0;
	return (fd);
}