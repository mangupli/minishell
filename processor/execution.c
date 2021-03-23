#include "minishell.h"

static int find_function(char **args)
{
	int i;

	if (!ft_strcmp(args[0], "exit"))
		return (7);
	else if (!ft_strcmp(args[0], "cd"))
		return (2);
	else if (!ft_strcmp(args[0], "export"))
		return (4);


	i = -1;
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
	execve(data->args[0], data->args, 0);
}

int  execution(t_data *data)
{
	pid_t pid;
	int status;
	int key;

	key = find_function(data->args);
	if (key == 7)
		ft_exit(0);
	else if (key == 1)
		shell_echo(data);
	else if (key == 2)
		shell_cd(data);
	else if (key == 3)
		shell_pwd(data);
	else if (key == 4)
		shell_export(data);
	else
	{
		pid = fork();
		if (pid == 0) //child
		{
			child_process(data);
		}
		else //parent
		{
			waitpid(-1, &status, 0);
			//printf("status %d\n", status);
			//exit(status);
		}
	}
	return (0);
}