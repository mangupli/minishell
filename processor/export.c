#include "minishell.h"
#include "parseader.h"

/*
** 1 - export without any arguments, 0 - env
*/

static void print_export(t_env *envs, int e)
{
	int i;

	i = 0;
	while (envs[i].name != NULL && envs[i].content != NULL)
	{
		if (e)
			ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(envs[i].name, 1);
		ft_putstr_fd("=", 1);
		if (!envs[i].content)
			ft_putstr_fd("\"\"", 1);
		else
		{
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(envs[i].content, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}

void		shell_export(t_data *data)
{
	if (!data->args[1])
	{
		print_export(data->env);
	}
}