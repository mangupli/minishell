#include "minishell.h"

static int func_in_return(t_data *data, char **args, void (*f)(t_data *, char **))
{
	f(data, args);
	return (1);
}

static int exec_my_function(char **args, char type, t_data *data)
{
	if (!ft_strcmp(args[0], "exit"))
	{
		if (argslstsize(data->ar) > 1)
			return (1);
		return (shell_exit(args, 0, data));
	}
	else if (!ft_strcmp(args[0], "cd"))
		return (func_in_return(data, args, shell_cd));
	else if (!ft_strcmp(args[0], "export"))
		return (func_in_return(data, args, shell_export));
	else if (!ft_strcmp(args[0], "unset"))
		return (func_in_return(data, args, shell_unset));
	args[0] = ft_str_to_lower(args[0]);
	if (!ft_strcmp(args[0], "echo"))
		return (func_in_return(data, args, shell_echo));
	else if (!ft_strcmp(args[0], "pwd"))
		return (func_in_return(data, args, shell_pwd));
	else if (!ft_strcmp(args[0], "env"))
		return (func_in_return(data, args, shell_env));
	return (0);
}

static int first_my_function(char **args, char type, t_data *data)
{
	if (!ft_strcmp(args[0], "exit"))
	{
		if (argslstsize(data->ar) > 1)
			return (1);
		return (shell_exit(args, 0, data));
	}
	else if (!ft_strcmp(args[0], "cd"))
		return (func_in_return(data, args, shell_cd));
	else if (!ft_strcmp(args[0], "export"))
		return (func_in_return(data, args, shell_export));
	else if (!ft_strcmp(args[0], "unset"))
		return (func_in_return(data, args, shell_unset));
	return (0);
}

static void parent_process(t_data *data)
{
	int ret;

	dup2(data->orig_fd[0], 0);
	dup2(data->orig_fd[1], 1);
	
	ret = waitpid(-1, &g_status, 0);
	if (g_status > 255)
		g_status %= 255;
	else if (WIFSIGNALED(g_status) && g_status != 2 && g_status != 3)			
		g_status += 128;
	
	errno = 0;
}

static void child_process(t_data *data, t_args *ar)
{
	int ret;

	ret = exec_my_function(ar->args, ar->type, data);
	if (ret)
	{
		//debug arguments
		//print_arguments(ar->args, 1);
		//end debug arguments
		exit(g_status);
	}
	if (!ft_strchr(ar->args[0], '/'))
	{
		ret = find_function_path(ar, data->envlist);
		if (ret == -1)
			ft_exit(-1, data, 0);
	}

	//debug arguments
	//print_arguments(ar->args, 0);
	//end debug arguments

	envlist_to_array(data);
	execve(ar->args[0], ar->args, data->envp);

	if (errno == 2) 
	{
		display_error("minishell", "command not found", ar->args[0]);
		ft_exit(127, data, 0);
	}
	else if (errno == 13)
	{
		display_error("minishell", ar->args[0], "permission denied");
		ft_exit(126, data, 0);
	}
	else
		ft_exit(-1, data, 0);
}

static void find_fd(t_data *data, t_args *ar)
{

	data->fd[0] = find_fdin(data, ar);
	data->fd[1] = find_fdout(data, ar);


	//printf("data->orig_fd[0]:%d | data->orig_fd[1]:%d\n", data->orig_fd[0], data->orig_fd[1]);
	//printf("data->fd[0]:%d | data->fd[1]:%d\n", data->fd[0], data->fd[1]);
	//printf("data->pipe_fd[0]:%d | data->pipe_fd[1]:%d\n", data->pipe_fd[0], data->pipe_fd[1]);
	//printf("ar->file_fd[0]:%d | ar->file_fd[1]:%d\n",ar->file[0], ar->file[1]);

	dup2(data->fd[0], 0);
	close(data->fd[0]);
	dup2(data->fd[1], 1);
	close(data->fd[1]);
}

static int processes(t_data *data, t_args *tmp)
{
	pid_t ret;

	find_fd(data, tmp);
	ret = fork();
	if (ret == 0)
		child_process(data, tmp);
	else if (ret > 0)
	{
		data->ar->pid = ret;
		parent_process(data);
	}
	else
	{
		display_error("minishell", NULL, strerror(errno));
		return (-1);
	}
	return (0);
}

void ft_wait(t_data *data, pid_t pid)
{
	int ret;

	ret = waitpid(pid, &g_status, 0);
	if (ret == -1)
		ft_exit(-1, data, 1);
}

int  execution(t_data *data)
{
	int ret;
	t_args *tmp;
	int i;

	tmp = data->ar;
	while (tmp)
	{
		if (tmp->args && tmp->args[0])
		{

			if (tmp->type == 0)
			{
				ret = first_my_function(tmp->args, tmp->type, data);
				if (ret)
				{
					//debug arguments
					//print_arguments(tmp->args, 1);
					//end debug arguments
					return (0);
				}
			}
			ret = processes(data, tmp);
			if (ret == -1)
				return (-1);
			reset_fd(data, tmp->file);
		}
		tmp = tmp->next;
	}
	/*
	ret = waitpid(-1, &g_status, 0);
	if (g_status > 255)
		g_status %= 255;
	else if (WIFSIGNALED(g_status) && g_status != 2 && g_status != 3)			
		g_status += 128;
		*/
	return (0);
}
