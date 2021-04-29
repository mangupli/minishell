#include "minishell.h"

static void	print_export(t_list_env *envs)
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

void		change_content(t_list_env **envs, t_list_env *new)
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
			else
				tmp->content = ft_strdup(new->content);
		}
		tmp = tmp->next;
	}
}

void	envsclear_node(t_list_env *env)
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

void	add_content(t_list_env **envs, t_list_env *new)
{
	t_list_env	*tmp;
	char		*save;

	tmp = *envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, new->name))
		{
			tmp->has_equal = new->has_equal;
			if (tmp->content)
			{
				save = tmp->content;
				tmp->content = ft_strjoin(save, new->content);
				free(save);
			}
			else
				tmp->content = ft_strdup(new->name);
		}
		tmp = tmp->next;
	}
}

void	exec_export(int symbols, t_list_env **envs, t_list_env *new)
{
	int			found;
	
	found = find_envvar(envs, new->name);
	if (found)
	{
		if (symbols == 2)
			add_content(envs, new);
		else
			change_content(envs, new);
		envsclear_node(new);
	}
	else
		env_lst_addback(envs, new);
}

/*
** Check_symbols() returns:
** 2 -- if there is '+=' in the string
** 1 -- if there is invalid indentifier somwhere before '='
** (valid - only letters and '_')
** 0 -- if the function didn't find anything
*/

void 		add_var_to_list(t_list_env **envs, char *str)
{
	t_list_env	*new;
	int			symbols;
	char		*tmp;

	symbols = check_symbols(str);
	if (symbols == 1)
	{
		g_status = 1;
		display_error("minishell", "export", "not a valid identifier");	
		return ;
	}
	new = envlstnew(str);
	if (symbols == 2)
	{
		tmp = new->name;
		new->name = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
		free(tmp);
	}
	exec_export(symbols, envs, new);
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
