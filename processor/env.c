#include "minishell.h"

static void print_env(t_env *envs)
{
	int i;

	i = 0;
	while (envs[i].name != NULL && envs[i].content != NULL)
	{
		if (envs[i].has_equal == 1)
		{
			ft_putstr_fd(envs[i].name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(envs[i].content, 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
}

void		shell_env(t_data *data)
{
	if (!data->args[1])
	{
		print_env(data->env);
	}
	else
	{
		display_error("env", data->args[1], "Too many arguments");
	}
}