#include "minishell.h"

int 	shell_echo(char **args)
{
	int flag;
	int i;

	if (args)
	{
		if (!args[1])
		{
			ft_putstr_fd("\n", 1);
			return (0);
		}
		i = 0;
		flag = 0;
		if (args[1] && !ft_strcmp(args[1], "-n"))
		{
			i++;
			flag = 1;
		}
		while (args[++i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] != NULL)
				ft_putstr_fd(" ", 1);
		}
		if (!flag)
			ft_putstr_fd("\n", 1);
	}
	return (0);
}
