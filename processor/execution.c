#include "minishell.h"

int 	execution(char *line, t_data *data)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0) // child
	{
		if (!ft_strcmp(data->args[0], "echo"))
			shell_echo(data->args);
		execve(line, data->args, 0);
	}
	else //parent
	{
		waitpid(-1, &status, 0);
		//exit(status);
	}
	return (0);
}