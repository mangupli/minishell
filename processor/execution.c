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

static void parent_process(t_data *data)
{
	int status;

	dup2(data->orig_fd[0], 0);
	dup2(data->orig_fd[1], 1);
	waitpid(-1, &status, 0);
	//printf("status %d\n", status);
	//exit(status);
}

static void child_process(t_data *data)
{
	execve(data->ar->args[0], data->ar->args, 0);
}

int  execution(t_data *data)
{
	pid_t pid;
	int ret;
	t_args *tmp;

	tmp = data->ar;
	while (tmp)
	{
		//debugging args
		int z = -1;
		while(tmp->args[++z])
			printf("args[%d]:%s\n", z, tmp->args[z]);
		//end debug

		ret = exec_my_function(tmp->args, data);
		if (ret)
		{
			tmp = tmp->next;
			continue ;
		}
		ret = find_function_path(tmp->args[0], data->envlist, data);
		if (ret)
		{
			data->fd[0] = find_fdin(data);
			data->fd[1] = find_fdout(data);

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
				child_process(data);
			}
			else //parent
			{
				parent_process(data);
			}
		}
		else
		{
			display_error("minishell", "command not found", tmp->args[0]);
		}
		tmp = tmp->next;
	}
	return (0);
}
