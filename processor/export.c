#include "minishell.h"
#include "parseader.h"

static void print_export(t_env *envs)
{
	int i;

	i = 0;
	while (envs[i].name != NULL && envs[i].content != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(envs[i].name, 1);
		if (envs[i].has_equal == '1' && !ft_strcmp(envs[i].content, ""))
			ft_putstr_fd("=\"\"", 1);
		else if (envs[i].has_equal == '1' && ft_strcmp(envs[i].content, ""))
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(envs[i].content, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}

static void		add_export_var(t_data *data)
{
	int i;

	i = 1;
	while (data->args[i])
	{
		if (!find_env(data->env, data->args[i]))
		{
			printf("new %s\n", data->args[i]);
			add_env(data->env, data->args[i], "");
			printf("added %s\n", data->args[i]);
		}
		printf("%d\n", i);
		i++;
	}
}

void		shell_export(t_data *data)
{
	if (!data->args[1])
	{
		print_export(data->env);
	}
	else
	{
		add_export_var(data);

	}
}

void		shell_unset(t_data *data)
{

}