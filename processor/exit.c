#include "minishell.h"

void 	ft_exit(int errcode, t_data *data, char hist)
{
	int ret;

	close_all_redir_fd(data);
	close(data->orig_fd[0]);
	close(data->orig_fd[1]);
	//printf("exited from %d with flag = %d\n", getpid(), hist);
	//printf("mother = %d\n", getppid());
	if (errcode == -1 && errno)
		display_error("minishell", NULL, strerror(errno));
	if (hist == 1)
		save_history(data); // Save the list on disk.
	exit(errcode);
}

int			shell_exit(char **args, int errcode, t_data *data)
{
	if (args[0] && args[1])
	{
		if (!ft_str_is_numeric(args[1]))
		{
			display_error("minishell : exit", args[1], "numeric argument required");
			ft_exit(-1, data, 1);
		}
		else if (args[2])
		{
			display_error("minishell", "exit", "too many arguments");
			g_status = 1;
			return (1);
		}
		else
		{
			errcode = ft_atoi(args[1]);
		}
	}
	ft_exit(errcode, data, 1);
	return (1);
}

void		display_error(char *commandname, char *errname, char *str)
{
	if (commandname)
	{
		ft_putstr_fd(commandname, 2);
		ft_putstr_fd(": ", 2);
	}
	if (errname)
	{
		ft_putstr_fd(errname, 2);
		ft_putstr_fd(": ", 2);
	}
	if (str)
		ft_putendl_fd(str, 2);
}
