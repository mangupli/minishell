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
	{
		printf("here\n");
		return (func_in_return(data, args, shell_cd));
	}
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
	//printf("status %d\n", status);
	//exit(status);
}

static void child_process(t_data *data, t_args *ar)
{
	int ret;

	ret = exec_my_function(ar->args, data);
	if (ret)
		exit(0);
	ret = find_function_path(ar, data->envlist);
	if (ret)
	{
		envlist_to_array(data);
		printf("execve->[%s]\n", ar->args[0]);
		execve(ar->args[0], ar->args, data->envp);
	}
	else
	{
		display_error("minishell", "command not found", ar->args[0]);
		exit(127);
	}
}

int  execution(t_data *data)
{
	pid_t pid;
	int ret;
	t_args *tmp;

	if (!ft_strcmp(data->ar->args[0], "exit"))
		ft_exit(0);
	tmp = data->ar;
	while (tmp)
	{
		//debugging args
		int z = -1;
		printf("after parser\n");
		while(tmp->args[++z])
			printf("args[%d]:%s\n", z, tmp->args[z]);
		//end debug

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
