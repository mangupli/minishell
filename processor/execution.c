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
	/*
	data->fd[0] = find_fdin(data);
	data->fd[1] = find_fdout(data);
	dup2(data->fd[0], 0);
	close(data->fd[0]);
	dup2(data->fd[1], 1);
	close(data->fd[1]);
	 */
	execve(data->ar->args[0], data->ar->args, 0);
}

int  execution(t_data *data)
{
	pid_t pid;
	int status;
	int ret;
	t_args *head;

	head = data->ar;
	while (data->ar)
	{
		//debugging args
		int z = -1;
		while(data->ar->args[++z])
			printf("args[%d]:%s\n", z, data->ar->args[z]);

		ret = exec_my_function(data->ar->args, data);
		if (ret)
			return (0);
		ret = find_function_path(data->ar->args[0], data->envlist, data);
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
				//data->ar = data->ar->next;
				//printf("status %d\n", status);
				//exit(status);
			}
		}
		else
			display_error("minishell", "command not found", data->ar->args[0]);
		data->ar = data->ar->next;
	}
	data->ar = head;
	return (0);
}
