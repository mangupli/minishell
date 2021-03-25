#include "minishell.h"

static void print_env(t_list_env *envs)
{
	t_list_env *tmp;

	tmp = envs;
	while (tmp)
	{
		if (tmp->has_equal == 1)
		{
			ft_putstr_fd(tmp->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(tmp->content, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
}

void		shell_env(t_data *data)
{
	if (!data->args[1])
	{
		print_env(data->envlist);
	}
	else
	{
		display_error("env", data->args[1], "Too many arguments");
	}
}

