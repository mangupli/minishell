#include "minishell.h"

static void print_export(t_list_env *envs)
{
	t_list_env *tmp;

	tmp = sort_list(envs);
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->name, 1);
		if (tmp->has_equal == 1 && !tmp->content)
			ft_putstr_fd("=\"\"", 1);
		if (tmp->has_equal == 1 && tmp->content)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->content, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}

void			change_content(t_list_env **envs, t_list_env *new)
{
	t_list_env *tmp;

	tmp = *envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, new->name))
		{
			tmp->has_equal = new->has_equal;
			if (tmp->content)
			{
				if (ft_strcmp(tmp->content, new->content))
				{
					free(tmp->content);
					tmp->content = ft_strdup(new->content);
				}
			}
		}
		tmp = tmp->next;
	}
}

void		add_export_var(t_data *data)
{
	int i;

	i = 1;
	while (data->args[i])
	{
		add_var_to_list(&data->envlist, data->args[i]);
		i++;
	}
}

void		shell_export(t_data *data)
{
	if (!data->args[1])
	{
		print_export(data->envlist);
	}
	else
	{
		add_export_var(data);
	}
}

void		shell_unset(t_data *data)
{

}