#include "minishell.h"
#include "parseader.h"

static int func_in_return(t_data *data, void (*f)(t_data *))
{
	f(data);
	return (1);
}

static int exec_my_function(char **args, t_data *data)
{
	int i;

	if (!ft_strcmp(args[0], "exit"))
		ft_exit(0);
	else if (!ft_strcmp(args[0], "cd"))
		return (func_in_return(data, shell_cd));
	else if (!ft_strcmp(args[0], "export"))
		return (func_in_return(data, shell_export));
	else if (!ft_strcmp(args[0], "unset"))
		return (func_in_return(data, shell_unset));
	i = -1;
	while (args[++i])
		args[i] = ft_str_to_lower(args[i]);
	if (!ft_strcmp(args[0], "echo"))
		return (func_in_return(data, shell_echo));
	else if (!ft_strcmp(args[0], "pwd"))
		return (func_in_return(data, shell_pwd));
	else if (!ft_strcmp(args[0], "env"))
		return (func_in_return(data, shell_env));
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
	int ret;

	ret = exec_my_function(data->args, data);
	if (ret)
		return (0);
	ret = find_function_path(data->args[0], data->envlist, data);
	if (ret)
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
	else
		display_error("minishell", "command not found", data->args[0]);
	return (0);
}
