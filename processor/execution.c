#include "minishell.h"
#include "parseader.h"

static int find_function(char **args)
{
	int i;

	if (!ft_strcmp(args[0], "exit"))
		return (7);
	else if (!ft_strcmp(args[0], "cd"))
		return (2);
	else if (!ft_strcmp(args[0], "export"))
		return (4);
	else if (!ft_strcmp(args[0], "unset"))
		return (5);
	i = -1;
	while (args[++i])
		args[i] = ft_str_to_lower(args[i]);
	if (!ft_strcmp(args[0], "echo"))
		return (1);
	else if (!ft_strcmp(args[0], "pwd"))
		return (3);
	else if (!ft_strcmp(args[0], "env"))
		return (6);
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
	char *function;

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
	else if (key == 6)
		shell_env(data);
	else if (key == 5)
		shell_unset(data);
	else
	{
		find_function_path(data->args[0], data->envlist, data);
		if (function)
		{
			pid = fork();
			if (pid == 0) //child
			{
				child_process(data);
			} else //parent
			{
				waitpid(-1, &status, 0);
				//printf("status %d\n", status);
				//exit(status);
			}
		}
		else
			display_error("minishell", "command not found", data->args[0]);
	}
	return (0);
}