#include "minishell.h"

t_list_env	*find_env_pointer(t_list_env *envs, char *name)
{
	t_list_env	*tmp;

	tmp = envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*get_envstring(t_list_env *var)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	if (var)
	{
		str = ft_strjoin(tmp, var->name);
		if (var->has_equal == 1)
		{
			tmp = ft_strjoin(str, "=");
			ft_free((void **)&str);
			if (var->content)
			{
				str = ft_strjoin(tmp, var->content);
				ft_free((void **)&tmp);
			}
		}
	}
	return (str);
}

void	envlist_to_array(t_data *data)
{
	char		**envp;
	t_list_env	*tmp;
	int			i;
	int			k;

	if (data->envp)
		free_2d_array(data->envp, 0);
	i = envlstsize(data->envlist);
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (envp == NULL)
		return ;
	tmp = data->envlist;
	k = -1;
	while (++k < i)
	{
		envp[k] = get_envstring(tmp);
		tmp = tmp->next;
	}
	envp[i] = NULL;
	data->envp = envp;
}

static void	print_env(t_list_env *envs)
{
	t_list_env	*tmp;

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

void	shell_env(t_data *data, char **args)
{
	if (!args[1])
	{
		print_env(data->envlist);
	}
	else
	{
		g_status = 127;
		display_error("env", args[1], "Too many arguments");
	}
}
