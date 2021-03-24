#include "minishell.h"
#include "parseader.h"

static void print_export(t_list_env *envs)
{
	t_list_env *tmp;

	tmp = envs;
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

static int	find_envvar(t_list_env *envs, char *name)
{
	t_list_env *tmp;

	tmp = envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
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

static int check_symbols(char *name, char *content)
{
	int i;

	i = -1;
	if (ft_isdigit(name[0]))
		return (1);
	return (0);
}

static void		add_export_var(t_data *data)
{
	int i;
	t_list_env *new;
	int found;

	i = 1;
	while (data->args[i])
	{
		new = ft_mylstnew(data->args[i]);
		found = find_envvar(data->envlist, new->name);
		if (found)
		{
			change_content(&data->envlist, new);
		}
		else
		{
			found = check_symbols(new->name, new->content);
			if (!found)
				ft_mylstadd_back(&data->envlist, new);
			else
			{
				display_error("minishell", "export", "not a valid identifier");
			}
		}
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