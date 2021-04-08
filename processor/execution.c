#include "minishell.h"

static int func_in_return(t_data *data, char **args, void (*f)(t_data *, char **))
{
	f(data, args);
	return (1);
}

static int exec_my_function(char **args, t_data *data)
{
	int i;

	if (!ft_strcmp(args[0], "exit"))
		ft_exit(0);
	else if (!ft_strcmp(args[0], "cd"))
		return (func_in_return(data, args, shell_cd));
	else if (!ft_strcmp(args[0], "export"))
		return (func_in_return(data, args, shell_export));
	else if (!ft_strcmp(args[0], "unset"))
		return (func_in_return(data, args, shell_unset));
	i = -1;
	while (args[++i])
		args[i] = ft_str_to_lower(args[i]);
	if (!ft_strcmp(args[0], "echo"))
		return (func_in_return(data, args, shell_echo));
	else if (!ft_strcmp(args[0], "pwd"))
		return (func_in_return(data, args, shell_pwd));
	else if (!ft_strcmp(args[0], "env"))
		return (func_in_return(data, args, shell_env));
	return (0);
}

static void parent_process(t_data *data)
{
	int status;

	dup2(data->orig_fd[0], 0);
	dup2(data->orig_fd[1], 1);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		//printf("exit status %d\n", status);
		status = WEXITSTATUS(status);
		printf("exit code = %d\n", status);
	}
	else if (WIFSIGNALED(status))
	{
		printf("signal status %d\n", status);
		status = status / 256;
		printf("status / 256 %d\n", status);
	}
	//printf("status %d\n", status);
}

static void child_process(t_data *data, t_args *ar)
{
	int ret;

	ret = exec_my_function(ar->args, data);
	if (ret)
		exit(0);
	if (!ft_strchr(ar->args[0], '/'))
		find_function_path(ar, data->envlist);

	envlist_to_array(data);

	//debugging args
	int z = 0;
	printf("execve->[%s]\n", ar->args[0]);
	while(ar->args[++z])
		printf("args[%d]:%s\n", z, ar->args[z]);
	//end debug

	ret = execve(ar->args[0], ar->args, data->envp);
	if (ret == -1)
	{
		display_error("minishell", "command not found", ar->args[0]);
		ft_exit(127); // but what errno returns?
	}
}

int  execution(t_data *data)
{
	pid_t pid;
	int ret;
	t_args *tmp;

	tmp = data->ar;
	while (tmp)
	{
		if (tmp->type == 0)
		{
			ret = exec_my_function(tmp->args, data);
			if (ret)
				return (0);
		}
		data->fd[0] = find_fdin(data);
		data->fd[1] = find_fdout(data, tmp->type);

	/*
		printf("data->orig_fd[0]:%d | data->orig_fd[1]:%d\n", data->orig_fd[0], data->orig_fd[1]);
		printf("data->fd[0]:%d | data->fd[1]:%d\n", data->fd[0], data->fd[1]);
		printf("data->pipe_fd[0]:%d | data->pipe_fd[1]:%d\n", data->pipe_fd[0], data->pipe_fd[1]);
	*/

		dup2(data->fd[0], 0);
		close(data->fd[0]);
		dup2(data->fd[1], 1);
		close(data->fd[1]);
		pid = fork();
		if (pid == 0) //child
		{
			child_process(data, tmp);
		}
		else //parent
		{
			parent_process(data);
		}
		tmp = tmp->next;
		reset_fd(data);
	}
	return (0);
}
