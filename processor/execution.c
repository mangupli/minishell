#include "minishell.h"

static int find_function(char **args)
{
	int i;

	i = -1;
	if (!ft_strcmp(args[0], "exit"))
		return (7);
	while (args[++i])
		args[i] = ft_str_to_lower(args[i]);
	if (!ft_strcmp(args[0], "echo"))
		return (1);
	else if (!ft_strcmp(args[0], "pwd"))
		return (3);
	return (0);
}


static void child_process(t_data *data)
{
	int key;

	key = find_function(data->args);
	if (key == 7)
	{
		//exit
	}
	else if (key == 1)
		shell_echo(data->args);
	else if (key == 3)
		shell_pwd(data->args);
	else
		execve(data->args[0], data->args, 0);
}

int execution(t_data *data)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0) // child
	{
		child_process(data);
	}
	else // parent
	{
		waitpid(-1, &status, 0);
		//exit(status);
	}
	return (0);
}