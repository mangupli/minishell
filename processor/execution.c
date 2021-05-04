#include "minishell.h"

static void	parent_process(t_data *data)
{
	dup2(data->orig_fd[0], 0);
	dup2(data->orig_fd[1], 1);
	waitpid(-1, &g_struct.status, 0);
	if (g_struct.status > 255)
	{
		g_struct.status %= 255;
	}
	else if (WIFSIGNALED(g_struct.status) && g_struct.status != 130 \
													&& g_struct.status != 131)
		g_struct.status += 128;
	errno = 0;
}

static void	child_process(t_data *data, t_args *ar)
{
	int	ret;

	ret = exec_my_function(ar->args, data);
	if (ret)
		exit(g_struct.status);
	if (!ft_strchr(ar->args[0], '/'))
	{
		ret = find_function_path(ar, data->envlist);
		if (ret == -1)
			ft_exit(-1, data, 0);
	}
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

static void	find_fd(t_data *data, t_args *ar)
{
	data->fd[0] = find_fdin(data, ar);
	data->fd[1] = find_fdout(data, ar);
	dup2(data->fd[0], 0);
	close(data->fd[0]);
	dup2(data->fd[1], 1);
	close(data->fd[1]);
}

static int	processes(t_data *data, t_args *tmp)
{
	pid_t	ret;

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

int	execution(t_data *data)
{
	int		ret;
	t_args	*tmp;

	tmp = data->ar;
	while (tmp)
	{
		if (tmp->args && tmp->args[0])
		{
			if (tmp->type == 0)
			{
				ret = first_my_function(tmp->args, data);
				if (ret)
				{
					return (0);
				}
			}
			ret = processes(data, tmp);
			if (ret == -1)
				return (-1);
			reset_fd(tmp->file);
		}
		tmp = tmp->next;
	}
	return (0);
}
