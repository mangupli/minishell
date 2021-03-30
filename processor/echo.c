#include "minishell.h"

void 	shell_echo(t_data *data)
{
	int flag;
	int i;

	if (data->ar->args)
	{
		if (!data->ar->args[1])
		{
			ft_putstr_fd("\n", 1);
			return ;
		}
		i = 0;
		flag = 0;
		if (data->ar->args[1] && !ft_strcmp(data->ar->args[1], "-n"))
		{
			i++;
			flag = 1;
		}
		while (data->ar->args[++i])
		{
			ft_putstr_fd(data->ar->args[i], 1);
			if (data->ar->args[i + 1] != NULL)
				ft_putstr_fd(" ", 1);
		}
		if (!flag)
			ft_putstr_fd("\n", 1);
	}
}
