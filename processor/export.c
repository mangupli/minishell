#include "minishell.h"

static void print_export(t_list_env *envs)
{
	t_list_env *new_list;
	t_list_env *tmp;

	new_list = sort_list(envs);
	tmp = new_list;
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
	envslst_clear(&new_list);
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

void envsclear_node(t_list_env *env)
{
	if (env)
	{
		if (env->name)
			free(env->name);
		if (env->content)
			free(env->content);
		free(env);
		env = NULL;
	}
}



void 		add_var_to_list(t_list_env **envs, char *str)
{
	t_list_env *new;
	int found;

	new = envlstnew(str);
	found = find_envvar(envs, new->name);
	if (found)
	{
		change_content(envs, new);
		envsclear_node(new);
	}
	else
	{
		found = check_symbols(new->name);
		if (!found)
			env_lst_addback(envs, new);
		else
		{
			g_status = 1;
			display_error("minishell", "export", "not a valid identifier");
		}
	}

}

void		add_export_var(t_data *data, char **args)
{
	int i;

	i = 1;
	while (args[i])
	{
		add_var_to_list(&data->envlist, args[i]);
		i++;
	}
}

void		shell_export(t_data *data, char **args)
{
	if (!args[1])
	{
		print_export(data->envlist);
	}
	else
	{
		add_export_var(data, args);
	}
}
