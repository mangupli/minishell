#include "minishell.h"

int 	shell_echo(t_data *data)
{
	int flag;
	int i;

	if (data->args)
	{
		if (!data->args[1])
		{
			ft_putstr_fd("\n", 1);
			return (0);
		}
		i = 0;
		flag = 0;
		if (data->args[1] && !ft_strcmp(data->args[1], "-n"))
		{
			i++;
			flag = 1;
		}
		while (data->args[++i])
		{
			ft_putstr_fd(data->args[i], 1);
			if (data->args[i + 1] != NULL)
				ft_putstr_fd(" ", 1);
		}
		if (!flag)
			ft_putstr_fd("\n", 1);
	}
	return (0);
}
